#pragma once
#include <Windows.h>

// Variables
//
extern int GlobalSmileId;
extern int Width;
extern int Height;
extern int LeftFlags;
extern int TimerSeconds;


// Windowing Functions Variables
// 1 -> New Game: Set on InitializeNewGame. 
//		The flag is used in couple places to check if the game is not in a finished state:
//			- 	
//			- NotifyWindowRestore: Before setting IsTimerOnAndShowed to IsTimerOnTemp back 
// 2 -> Window is minimized! 
//		This flag is used before setting IsTimerOnTemp to IsTimerOnAndShowed
// 4 -> ??
// 8 -> Another window is minimized flag: 
//	This flag is used in case of WINDOWPOSCHANGED, The X_pos and Y_pos is updated
// 0x10 -> Set on FinishGame()
// This state variable is very bad from a code quality point of view
// Why don't you just use different variables
#define STATE_GAME_IS_ON 0b01
#define STATE_WINDOW_MINIMIZED  0b10
#define STATE_WINDOW_MINIMIZED_2 0b1000
#define STATE_GAME_FINISHED 0b10000
extern int StateFlags;

// Enum Data
//
// Block Data:
// 8 bits:
// [ [is_bomb: 8] [revealed: 7] [unused: 6] [state: 5 4 3 2 1] ] 
#define BLOCK_STATE_BORDER_VALUE 0x10
#define BLOCK_STATE_EMPTY_UNCLICKED 0xF
#define BLOCK_STATE_FLAG 0xE
#define BLOCK_STATE_QUESTION_MARK 0xD
#define BLOCK_STATE_BOMB_RED_BACKGROUND 0xC
#define BLOCK_STATE_BOMB_WITH_X 0xB
#define BLOCK_STATE_BLACK_BOMB 0xA
#define BLOCK_STATE_CLICKED_QUESTION_MARK 9
#define BLOCK_STATE_NUMBER_8 8
#define BLOCK_STATE_NUMBER_7 7
#define BLOCK_STATE_NUMBER_6 6
#define BLOCK_STATE_NUMBER_5 5
#define BLOCK_STATE_NUMBER_4 4
#define BLOCK_STATE_NUMBER_3 3
#define BLOCK_STATE_NUMBER_2 2
#define BLOCK_STATE_NUMBER_1 1
#define BLOCK_STATE_READ_EMPTY 0
#define BLOCK_STATE_MASK 0x1F

#define BLOCK_IS_REVEALED 0x40
#define BLOCK_IS_BOMB 0x80

// Maybe the "Block" is declared as struct with bit fields..?
#define BLOCK_IS_STATE(Block, State) ((Block & BLOCK_STATE_MASK) == State)

typedef struct {
    int Column;
    int Row;
} BoardPoint;

extern BoardPoint ClickedBlock;
extern BYTE BlockArray[27][32];

#define ACCESS_BLOCK(point) (BlockArray[point.Row][point.Column])

BOOL InitializeBitmapsAndBlockArray();
__inline BOOL IsInBoardRange(BoardPoint point);
void ChangeBlockState(BoardPoint point, BYTE blockState);
void InitializeBlockArrayBorders();
int CountNearBombs(BoardPoint point);
void RevealAllBombs(BYTE revealedBombsState);
void TickSeconds();
void ShowBlockValue(BoardPoint point);
void ExpandEmptyBlock(BoardPoint point);
DWORD GetFlagBlocksCount(BoardPoint point);
void UpdateBlockStateToClicked(BoardPoint point);
void UpdateBlockStateToUnclicked(BoardPoint point);
__inline VOID UpdateClickedBlocksState3x3(BoardPoint newClick, BoardPoint oldClick);
__inline VOID UpdateClickedBlocksStateNormal(BoardPoint point, BoardPoint oldClick);
__inline void ReleaseBlocksClick();
void ReleaseMouseCapture(); // inline
void UpdateClickedBlocksState(BoardPoint point);
void NotifyMinimize();
void NotifyWindowRestore();
void AddAndDisplayLeftFlags(DWORD leftFlagsToAdd);
void FinishGame(BOOL isWon);
void HandleNormalBlockClick(BoardPoint point);
void Handle3x3BlockClick(BoardPoint point);
void InitializeNewGame();
void HandleRightClick(BoardPoint point);
void HandleBlockClick();
