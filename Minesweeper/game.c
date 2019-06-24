#include "game.h"
#include "windowing.h"
#include "config.h"
#include "sound.h"
#include "drawing.h"
#include "resource.h"
#include "utils.h"

DWORD StateFlags = STATE_GAME_FINISHED | STATE_WINDOW_MINIMIZED;

// Board Array Variables
BoardPoint ClickedBlock = { -1, -1 };
int GlobalSmileId;

// If this is FALSE, timer does not display time progress
// After calling "FinishGame" the flag is FALSE
// Calling InitializeNewGame() sets this to FALSE
// Before calling SetTimer(), set this to TRUE
BOOL IsTimerOnAndShowed;
BOOL IsTimerOnTemp;
int LeftFlags;


int ColumnsList[100];

int Mines_Copy;
// TODO: What is the difference between those variables
// TODO: Make sure I did not confuse these variables
int Width;
int Height;
BYTE BlockArray[27][32];



int CurrentRowColumnListIndex;
int TimerSeconds;

int NumberOfEmptyBlocks;
int NumberOfRevealedBlocks;
int RowsList[100];

BOOL InitializeBitmapsAndBlockArray() {
    if (LoadBitmaps()) {
        InitializeBlockArrayBorders();
        return TRUE;
    }

    return FALSE;
}

__inline void ReverseMemSet(PBYTE buffer, BYTE value, DWORD size) {
    do {
        size--;
        buffer[size] = value;
    } while (size != 0);
}

void InitializeBlockArrayBorders() {

    ReverseMemSet(BlockArray, BLOCK_STATE_EMPTY_UNCLICKED, sizeof(BlockArray));

    for (int column = Width + 1; column != 0; column--) {
        // Fill upper border
        BlockArray[0][column] = BLOCK_STATE_BORDER_VALUE;

        // Fill lower border
        BlockArray[Height + 1][column] = BLOCK_STATE_BORDER_VALUE;
    }

    for (int row = Height + 1; row != 0; row++) {
        // Fill left border
        BlockArray[row][0] = BLOCK_STATE_BORDER_VALUE;

        // Fill right border
        BlockArray[row][Width + 1] = BLOCK_STATE_BORDER_VALUE;
    }
}

void InitializeNewGame() {
    DWORD borderFlags;

    if (GameConfig.Width == Width && GameConfig.Height == Height) {
        borderFlags = WINDOW_BORDER_REPAINT_WINDOW;
    }
    else {
        borderFlags = WINDOW_BORDER_MOVE_WINDOW | WINDOW_BORDER_REPAINT_WINDOW;
    }

    Width = GameConfig.Width;
    Height = GameConfig.Height;

    InitializeBlockArrayBorders();

    GlobalSmileId = 0;

    // Setup all the mines
    Mines_Copy = GameConfig.Mines;

    do {
        BoardPoint randomPoint;

        // Find a location for the mine
        do {
            randomPoint = (BoardPoint) {
                .Column = GetRandom(Width) + 1,
                .Row = GetRandom(Height) + 1
            };

        } while (ACCESS_BLOCK(randomPoint) & BLOCK_IS_BOMB);

        // SET A MINE
        ACCESS_BLOCK(randomPoint) |= BLOCK_IS_BOMB;
        Mines_Copy--;
    } while (Mines_Copy);

    TimerSeconds = 0;
    Mines_Copy = GameConfig.Mines;
    LeftFlags = Mines_Copy;
    NumberOfRevealedBlocks = 0;
    NumberOfEmptyBlocks = (Height * Width) - GameConfig.Mines;
    StateFlags = STATE_GAME_IS_ON;
    AddAndDisplayLeftFlags(0); // Should have called DisplayLeftFlags()!
    InitializeWindowBorder(borderFlags);
}

void RevealAllBombs(BYTE revealedBombsState) {

    for (int loop_row = 1; loop_row <= Height; ++loop_row) {
        for (int loop_column = 1; loop_column <= Width; ++loop_column) {
            PBYTE pBlock = &BlockArray[loop_row][loop_column];

            if (*pBlock & BLOCK_IS_REVEALED) {
                continue;
            }

            BYTE blockState = *pBlock & BLOCK_STATE_MASK;

            if (*pBlock & BLOCK_IS_BOMB) {
                if (blockState != BLOCK_STATE_FLAG) {
                    *pBlock = (*pBlock & 0xe0) | revealedBombsState;
                }
            }
            else if (blockState == BLOCK_STATE_FLAG) {
                // This is not a bomb, but flagged by the user
                *pBlock = (*pBlock & 0xeb) | BLOCK_STATE_BOMB_WITH_X;
            }
        }
    }

    DisplayAllBlocks();
}

DWORD GetFlagBlocksCount(BoardPoint point) {
    DWORD flagsCount = 0;

    // Search in the sorrunding blocks
    for (int loop_row = (point.Row - 1); loop_row <= (point.Row + 1); ++loop_row) {
        for (int loop_column = (point.Column - 1); loop_column <= (point.Column + 1); ++loop_column) {

            BYTE blockValue = BlockArray[loop_row][loop_column] & BLOCK_STATE_MASK;

            if (blockValue == BLOCK_STATE_FLAG) {
                flagsCount++;
            }
        }

    }

    return flagsCount;
}



__inline BOOL IsInBoardRange(BoardPoint point) {
    return point.Column > 0 && point.Row > 0 && point.Column <= Width && point.Row <= Height;
}

__inline VOID UpdateClickedBlocksStateNormal(BoardPoint newClick, BoardPoint oldClick) {
    if (IsInBoardRange(oldClick) && (ACCESS_BLOCK(oldClick) & BLOCK_IS_REVEALED) == 0) {
        UpdateBlockStateToUnclicked(oldClick);
        DrawBlock(oldClick);
    }

    if (IsInBoardRange(newClick)) {
        const BYTE block = ACCESS_BLOCK(newClick);

        if ((block & BLOCK_IS_REVEALED) == 0 && !BLOCK_IS_STATE(block, BLOCK_STATE_FLAG)) {
            UpdateBlockStateToClicked(ClickedBlock);
            DrawBlock(ClickedBlock);
        }
    }
}

__inline VOID UpdateClickedBlocksState3x3(BoardPoint newClick, BoardPoint oldClick) {
    BOOL isNewLocationInBounds = IsInBoardRange(newClick);
    BOOL isOldLocationInBounds = IsInBoardRange(oldClick);

    // Get 3x3 bounds for the old and new clicks
    int oldTopRow = max(1, oldClick.Row - 1);
    int oldBottomRow = min(Height, oldClick.Row + 1);

    int topRow = max(1, newClick.Row - 1);
    int bottomRow = min(Height, newClick.Row + 1);

    int oldLeftColumn = max(1, oldClick.Column - 1);
    int oldRightColumn = min(Width, oldClick.Column + 1);

    int leftColumn = max(1, newClick.Column - 1);
    int rightColumn = min(Width, newClick.Column + 1);

    // Change old to unclicked. WIERD: Missing bounds check
    for (int loop_row = oldTopRow; loop_row <= oldBottomRow; loop_row++) {
        for (int loop_column = oldLeftColumn; loop_column <= oldRightColumn; ++loop_column) {
            if ((BlockArray[loop_row][loop_column] & BLOCK_IS_REVEALED) == 0) {
                UpdateBlockStateToUnclicked((BoardPoint) { loop_column, loop_row });
            }
        }
    }

    // Change new to clicked
    if (isNewLocationInBounds) {
        for (int loop_row = topRow; loop_row <= bottomRow; ++loop_row) {
            for (int loop_column = leftColumn; loop_column <= rightColumn; loop_column++) {
                if ((BlockArray[loop_row][loop_column] & BLOCK_IS_REVEALED) == 0) {
                    UpdateBlockStateToClicked((BoardPoint) { loop_column, loop_row });
                }
            }
        }
    }

    // Draw old blocks
    if (isOldLocationInBounds) {
        for (int loop_row = oldTopRow; loop_row <= oldBottomRow; loop_row++) {
            for (int loop_column = oldLeftColumn; loop_column <= oldRightColumn; ++loop_column) {
                DrawBlock((BoardPoint) { loop_column, loop_row });
            }
        }
    }

    if (isNewLocationInBounds) {
        for (int loop_row = topRow; loop_row <= bottomRow; ++loop_row) {
            for (int loop_column = leftColumn; loop_column <= rightColumn; ++loop_column) {
                DrawBlock((BoardPoint) { loop_column, loop_row });
            }
        }
    }
}

__inline void ReleaseBlocksClick() {
    UpdateClickedBlocksState((BoardPoint) { -2, -2 });
}

void UpdateClickedBlocksState(BoardPoint point) {
    if (point.Column == ClickedBlock.Column && point.Row == ClickedBlock.Row) {
        return;
    }

    // Save old click point
    const BoardPoint oldClickPoint = ClickedBlock;

    // Update new click point
    ClickedBlock = point;

    if (Is3x3Click) {
        UpdateClickedBlocksState3x3(point, oldClickPoint);
    }
    else {
        UpdateClickedBlocksStateNormal(point, oldClickPoint);
    }

}

void UpdateBlockStateToClicked(BoardPoint point) {
    PBYTE pBlock = &ACCESS_BLOCK(point);
    BYTE BlockFlags = *pBlock & BLOCK_STATE_MASK;

    if (*pBlock == BLOCK_STATE_QUESTION_MARK) {
        BlockFlags = BLOCK_STATE_CLICKED_QUESTION_MARK;
    }
    else if (*pBlock == BLOCK_STATE_EMPTY_UNCLICKED) {
        BlockFlags = BLOCK_STATE_READ_EMPTY;
    }

    // Clean the block state    
    // set the block state
    *pBlock = (*pBlock & ~BLOCK_STATE_MASK) | BlockFlags;
}

void UpdateBlockStateToUnclicked(BoardPoint point) {
    PBYTE pBlock = &ACCESS_BLOCK(point);
    BYTE Block = *pBlock & BLOCK_STATE_MASK;
    BYTE res;

    if (Block == BLOCK_STATE_CLICKED_QUESTION_MARK || Block == BLOCK_STATE_READ_EMPTY) {
        res = BLOCK_STATE_QUESTION_MARK;
    }
    else {
        res = BLOCK_STATE_EMPTY_UNCLICKED;
    }

    *pBlock = (Block & BLOCK_STATE_FLAG) | res;
}

void FinishGame(BOOL isWon) {
    IsTimerOnAndShowed = FALSE;
    GlobalSmileId = (isWon) ? SMILE_WINNER : SMILE_LOST;
    DisplaySmile(GlobalSmileId);

    // If the player wins, bombs are changed into borderFlags
    // If the player loses, bombs change into black bombs
    RevealAllBombs((isWon) ? BLOCK_STATE_FLAG : BLOCK_STATE_BLACK_BOMB);

    if (isWon && LeftFlags != 0) {
        AddAndDisplayLeftFlags(-LeftFlags);
    }

    PlayGameSound(isWon ? SOUNDTYPE_WIN : SOUNDTYPE_LOSE);
    StateFlags = STATE_GAME_FINISHED;

    // Check if it is the best time
    if (isWon && GameConfig.Difficulty != DIFFICULTY_CUSTOM) {
        if (TimerSeconds < GameConfig.Times[GameConfig.Difficulty]) {
            GameConfig.Times[GameConfig.Difficulty] = TimerSeconds;
            SaveWinnerNameDialogBox();
            WinnersDialogBox();
        }
    }
}


int CountNearBombs(BoardPoint point) {
    int count = 0;

    for (int loop_row = (point.Row - 1); loop_row <= (point.Row + 1); loop_row++) {
        for (int loop_column = (point.Column - 1); loop_column <= (point.Column + 1); loop_column++) {
            if (BlockArray[loop_row][loop_column] & BLOCK_IS_BOMB) {
                count++;
            }
        }
    }

    return count;
}

void ShowBlockValue(BoardPoint point) {

    BYTE blockValue = ACCESS_BLOCK(point);

    if (blockValue & BLOCK_IS_REVEALED) {
        return;
    }

    BYTE state = blockValue & BLOCK_STATE_MASK;

    if (state == BLOCK_STATE_BORDER_VALUE || state == BLOCK_STATE_FLAG) {
        return;
    }

    NumberOfRevealedBlocks++;

    int nearBombsCount = CountNearBombs(point);
    nearBombsCount |= BLOCK_IS_REVEALED;
    ACCESS_BLOCK(point) = nearBombsCount;
    DrawBlock(point);

    if (nearBombsCount == 0) {
        RowsList[CurrentRowColumnListIndex] = point.Row;
        ColumnsList[CurrentRowColumnListIndex] = point.Column;

        CurrentRowColumnListIndex++;

        if (CurrentRowColumnListIndex == 100) {
            CurrentRowColumnListIndex = 0;
        }
    }
}

// Called on button release
// Called on MouseMove 
void ReleaseMouseCapture() {
    HasMouseCapture = FALSE;
    ReleaseCapture();

    if (StateFlags & STATE_GAME_IS_ON) {
        // Mouse move always gets here
        ReleaseBlocksClick();
    }
    else {
        HandleBlockClick();
    }
}



void HandleRightClick(BoardPoint point) {
    if (IsInBoardRange(point)) {
        BYTE block = ACCESS_BLOCK(point);

        if (!(block & BLOCK_IS_REVEALED)) {
            BYTE blockState = block & BLOCK_STATE_MASK;

            switch (blockState) {
            case BLOCK_STATE_FLAG:
                blockState = (GameConfig.Mark) ? BLOCK_STATE_QUESTION_MARK : BLOCK_STATE_EMPTY_UNCLICKED;
                AddAndDisplayLeftFlags(1);
                break;
            case BLOCK_STATE_QUESTION_MARK:
                blockState = BLOCK_STATE_EMPTY_UNCLICKED;
                break;
            default: // Assume BLOCK_STATE_EMPTY_UNCLICKED
                blockState = BLOCK_STATE_FLAG;
                AddAndDisplayLeftFlags(-1);
            }

            ChangeBlockState(point, blockState);

            if (BLOCK_IS_STATE(block, BLOCK_STATE_FLAG) &&
                NumberOfRevealedBlocks == NumberOfEmptyBlocks) {
                FinishGame(TRUE);
            }
        }
    }
}


// Called when a button is released and the game is on
//
void HandleBlockClick() {
    if (IsInBoardRange(ClickedBlock)) {
        if (NumberOfRevealedBlocks == 0 && TimerSeconds == 0) {
            // First Click! Initialize Timer 
            PlayGameSound(SOUNDTYPE_TICK);
            TimerSeconds++;
            DisplayTimerSeconds();
            IsTimerOnAndShowed = TRUE;

            if (!SetTimer(hWnd, TIMER_ID, 1000, NULL)) {
                DisplayErrorMessage(ID_TIMER_ERROR);
            }
        }

        if (!(StateFlags & STATE_GAME_IS_ON)) {
            // WIERD: Setting this to -2, -2 causes buffer overflow
            ClickedBlock = (BoardPoint) { -2, -2 };
        }

        if (Is3x3Click) {
            Handle3x3BlockClick(ClickedBlock);
        }
        else {
            // WIERD: The buffer overflow occurs here
            // ClickedBlock might be (-2, -2)
            BYTE blockValue = ACCESS_BLOCK(ClickedBlock);

            if (!(blockValue & BLOCK_IS_REVEALED) && !BLOCK_IS_STATE(blockValue, BLOCK_STATE_FLAG)) {
                HandleNormalBlockClick(ClickedBlock);
            }
        }


    }

    DisplaySmile(GlobalSmileId);
}


void NotifyMinimize() {
    FreeSound();

    if ((StateFlags & STATE_WINDOW_MINIMIZED) == 0) {
        IsTimerOnTemp = IsTimerOnAndShowed;
    }

    if (StateFlags & STATE_GAME_IS_ON) {
        IsTimerOnAndShowed = FALSE;
    }

    StateFlags |= STATE_WINDOW_MINIMIZED;
}

void NotifyWindowRestore() {
    if (StateFlags & STATE_GAME_IS_ON) {
        IsTimerOnAndShowed = IsTimerOnTemp;
    }

    StateFlags &= ~(STATE_WINDOW_MINIMIZED);
}


void Handle3x3BlockClick(BoardPoint point) {
    BYTE blockValue = ACCESS_BLOCK(point);

    if ((blockValue & BLOCK_IS_REVEALED) && GetFlagBlocksCount(point) == blockValue) {
        BOOL lostGame = FALSE;

        for (int loop_row = (point.Row - 1); loop_row <= (point.Row + 1); ++loop_row) {
            for (int loop_column = (point.Column - 1); loop_column <= (point.Column + 1); ++loop_column) {
                BYTE blockValue = BlockArray[loop_row][loop_column];

                if (blockValue == BLOCK_STATE_FLAG || !(blockValue & BLOCK_IS_BOMB)) {
                    ExpandEmptyBlock((BoardPoint) { loop_column, loop_row });
                }
                else {
                    // The user clicked a bomb
                    lostGame = TRUE;
                    ChangeBlockState((BoardPoint) { loop_column, loop_row }, BLOCK_IS_REVEALED | BLOCK_STATE_BOMB_RED_BACKGROUND);
                }
            }
        }

        if (lostGame) {
            FinishGame(FALSE);
        }
        else if (NumberOfEmptyBlocks == NumberOfRevealedBlocks) {
            FinishGame(TRUE);
        }

    }
    else {
        ReleaseBlocksClick();
        return;

    }

}


void TickSeconds() {
    if (IsTimerOnAndShowed && TimerSeconds < 999) {
        TimerSeconds++;
        DisplayTimerSeconds();
        PlayGameSound(SOUNDTYPE_TICK);
    }
}

void ChangeBlockState(BoardPoint point, BYTE blockState) {
    PBYTE pBlock = &ACCESS_BLOCK(point);

    *pBlock = (*pBlock & 0xE0) | blockState;

    DrawBlock(point);
}

__inline void ReplaceFirstNonBomb(BoardPoint point, PBYTE pFunctionBlock) {
    // The first block! Change a normal block to a bomb, 
    // Replace the current block into an empty block
    // Reveal the current block
    // WIERD: LOOP IS WITHOUT AN EQUAL SIGN
    for (int current_row = 1; current_row < Height; ++current_row) {
        for (int current_column = 1; current_column < Width; ++current_column) {
            PBYTE pLoopBlock = &BlockArray[current_row][current_column];

            // Find the first non-bomb
            if (!(*pLoopBlock & BLOCK_IS_BOMB)) {
                // Replace bomb place
                *pFunctionBlock = BLOCK_STATE_EMPTY_UNCLICKED;
                *pLoopBlock |= BLOCK_IS_BOMB;

                ExpandEmptyBlock(point);
                return;
            }
        }
    }
}

void HandleNormalBlockClick(BoardPoint point) {
    PBYTE pFunctionBlock = &ACCESS_BLOCK(point);

    // Click an empty block
    if (!(*pFunctionBlock & BLOCK_IS_BOMB)) {
        ExpandEmptyBlock(point);

        if (NumberOfRevealedBlocks == NumberOfEmptyBlocks) {
            FinishGame(TRUE);
        }
    }
    // Clicked a bomb and it's the first block 
    else if (NumberOfRevealedBlocks == 0) {
        ReplaceFirstNonBomb(point, pFunctionBlock);
    }
    // Clicked A Bomb
    else {
        ChangeBlockState(point, BLOCK_IS_REVEALED | BLOCK_STATE_BOMB_RED_BACKGROUND);
        FinishGame(FALSE);
    }
}

void ExpandEmptyBlock(BoardPoint point) {

    CurrentRowColumnListIndex = 1;
    ShowBlockValue(point);

    int i = 1;

    while (i != CurrentRowColumnListIndex) {
        int row = RowsList[i];
        int column = ColumnsList[i];

        ShowBlockValue((BoardPoint) { column - 1, row - 1 });
        ShowBlockValue((BoardPoint) { column, row - 1 });
        ShowBlockValue((BoardPoint) { column + 1, row - 1 });

        ShowBlockValue((BoardPoint) { column - 1, row });
        ShowBlockValue((BoardPoint) { column + 1, row });

        ShowBlockValue((BoardPoint) { column - 1, row + 1 });
        ShowBlockValue((BoardPoint) { column, row + 1 });
        ShowBlockValue((BoardPoint) { column + 1, row + 1 });
        i++;

        if (i == 100) {
            i = 0;
        }
    }

}