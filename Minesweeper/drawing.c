#include <Windows.h>
#include "config.h"
#include "windowing.h"
#include "game.h"
#include "resource.h"
#include "drawing.h"
#include "sound.h"

#define POINT_BIG_NUM_X 17
#define POINT_MID_NUM_X 30
#define POINT_LOW_NUM_X 43

#define NUMBER_WIDTH 13
#define NUMBER_HEIGHT 23
#define NUMBER_Y 16

#define BLOCK_WIDTH 16
#define BLOCK_HEIGHT 16

#define SMILE_BITMAP_WIDTH 24
#define SMILE_BITMAP_HEIGHT 24

#define NUM_MINUS 11

HPEN hPen;

// Resource Handles
HGLOBAL hSmilesBitmapResource;
HGLOBAL hBlocksBitmapResource;
HGLOBAL hNumbersBitmapResource;

// Bitmap Info Pointer
PBITMAPINFO lpSmilesBitmapInfo;
PBITMAPINFO lpBlocksBitmapInfo;
PBITMAPINFO lpNumbersBitmapInfo;

// Bitmap Handles
HBITMAP BlockBitmaps[16];

// Indexes To Bitmaps
DWORD SmileBitmapIndex[5];
DWORD BlockBitmapIndex[16];
DWORD NumberBitmapIndex[12];


// Indexes are block states
HDC BlockStates[16];

HRSRC FindBitmapResource(USHORT resourceId) {
    // If there is no color, 
    // Get the next resource which is color-less
    if (!GameConfig.Color) {
        resourceId++;
    }

    return FindResourceW(hModule, (LPCWSTR)(resourceId), (LPWSTR)RT_BITMAP);
}

BOOL LoadBitmaps() {
    if (!LoadBitmapResources()) {
        return FALSE;
    }

    InitializePen();

    InitializeBitmapsIndexes();

    ProcessBlockBitmaps();

    return TRUE;
}

__inline void InitializePen() {
    if (GameConfig.Color) {
        hPen = CreatePen(PS_SOLID, 1, RGB(128, 128, 128));
    }
    else {
        hPen = (HPEN)GetStockObject(BLACK_PEN);
    }
}

__inline void ProcessBlockBitmaps() {
    HDC hWndDC = GetDC(hWnd);

    for (int i = 0; i < _countof(BlockStates); ++i) {
        BlockStates[i] = CreateCompatibleDC(hWndDC);

        if (BlockStates[i] == NULL) {
            // Maybe that means the original name of the function was "FLoad"
            // This is a bad name dude. 
            OutputDebugStringA("FLoad failed to create compatible dc\n");
        }

        BlockBitmaps[i] = CreateCompatibleBitmap(hWndDC, 16, 16);

        if (BlockBitmaps[i] == NULL) {
            OutputDebugStringA("Failed to create Bitmap\n");
        }

        // Mmm. BlockState[i] might be an invalid value, Also BlockBitmaps[i] 
        // Why would he perform this operation anyway.. :(
        SelectObject(BlockStates[i], BlockBitmaps[i]);
        SetDIBitsToDevice(BlockStates[i], 0, 0, BLOCK_WIDTH, BLOCK_HEIGHT,
            0, 0, 0, 16, BlockBitmapIndex[i] + lpBlocksBitmapInfo, lpBlocksBitmapInfo, 0);
    }

    ReleaseDC(hWnd, hWndDC);
}

__inline BOOL LoadBitmapResources() {
    hBlocksBitmapResource = TryLoadBitmapResource(ID_BITMAP_BLOCK);
    hNumbersBitmapResource = TryLoadBitmapResource(ID_BITMAP_NUMBERS);
    hSmilesBitmapResource = TryLoadBitmapResource(ID_BITMAP_SMILES);

    // Yea I know, it's wierd that the check is performed after all the resources are loaded..
    if (hSmilesBitmapResource == NULL || hBlocksBitmapResource == NULL || hNumbersBitmapResource == NULL) {
        return FALSE;
    }

    lpBlocksBitmapInfo = (PBITMAPINFO)LockResource(hBlocksBitmapResource);
    lpNumbersBitmapInfo = (PBITMAPINFO)LockResource(hNumbersBitmapResource);
    lpSmilesBitmapInfo = (PBITMAPINFO)LockResource(hSmilesBitmapResource);

    return TRUE;
}

__inline void InitializeBitmapsIndexes() {
#define COLORED_BMP_START 104
#define NONCOLORED_BMP_START 48

    const DWORD bitmapStartIndex = (GameConfig.Color) ? COLORED_BMP_START : NONCOLORED_BMP_START;

    InitializeBitmapIndexes(
        BlockBitmapIndex,           // indexesArray
        _countof(BlockBitmapIndex), // numberOfBitmaps
        bitmapStartIndex,           // firstBitmapIndex
        GetBitmapByteLength(BLOCK_WIDTH, BLOCK_HEIGHT) // bytesPerBitmap
    );

    InitializeBitmapIndexes(
        NumberBitmapIndex,         // indexesArray
        _countof(NumberBitmapIndex), // numberOfBitmaps
        bitmapStartIndex, // firstBitmapIndex
        GetBitmapByteLength(NUMBER_WIDTH, NUMBER_HEIGHT) // bytesPerBitmap
    );

    InitializeBitmapIndexes(
        SmileBitmapIndex, // indexesArray
        _countof(SmileBitmapIndex), // numberOfBitmaps
        bitmapStartIndex, // firstBitmapIndex
        GetBitmapByteLength(SMILE_BITMAP_WIDTH, SMILE_BITMAP_HEIGHT) // bytesPerBitmap
    );
}

__inline void InitializeBitmapIndexes(PDWORD indexesArray, int numberOfBitmaps, DWORD firstBitmapIndex, DWORD bytesPerBitmap) {
    for (int i = 0; i < numberOfBitmaps; ++i) {
        indexesArray[i] = firstBitmapIndex;
        firstBitmapIndex += bytesPerBitmap;
    }
}

__inline HGLOBAL TryLoadBitmapResource(USHORT resourceId) {
    HRSRC hRsrc = FindBitmapResource(resourceId);

    if (hRsrc != NULL) {
        return LoadResource(hModule, hRsrc);
    }

    return NULL;
}

void DisplayNumber(HDC hDC, int xPosition, int numberToDisplay) {
    SetDIBitsToDevice(hDC,
        xPosition, NUMBER_Y, NUMBER_WIDTH, NUMBER_HEIGHT, 0, 0, 0, 23,
        NumberBitmapIndex[numberToDisplay] + lpNumbersBitmapInfo, lpNumbersBitmapInfo, 0);

}

void AddAndDisplayLeftFlags(DWORD leftFlagsToAdd) {
    LeftFlags += leftFlagsToAdd;
    DisplayLeftFlags();
}

void DisplayLeftFlags() {
    HDC hDC = GetDC(hWnd);
    DisplayLeftFlagsOnDC(hDC);
    ReleaseDC(hWnd, hDC);
}

void DisplayLeftFlagsOnDC(HDC hDC) {
    DWORD layout = GetLayout(hDC);

    if (layout & 1) {
        // Set layout to Left To Right
        SetLayout(hDC, 0);
    }

    int lowDigit;
    int highNum;

    if (LeftFlags >= 0) {
        lowDigit = LeftFlags / 100;
        highNum = LeftFlags % 100;
    }
    else {
        lowDigit = NUM_MINUS;
        highNum = LeftFlags % 100;
    }

    DisplayNumber(hDC, POINT_BIG_NUM_X, lowDigit);
    DisplayNumber(hDC, POINT_MID_NUM_X, highNum / 10);
    DisplayNumber(hDC, POINT_LOW_NUM_X, highNum % 10);

    if (layout & 1) {
        SetLayout(hDC, layout);
    }
}

void FreePenAndBlocksAndSound() {
    FreePenAndBlocks();
    FreeSound();
}

void FreePenAndBlocks() {
    if (hPen != NULL) {
        DeleteObject(hPen);
    }

    for (int i = 0; i < 16; ++i) {
        DeleteDC(BlockStates[i]);
        DeleteObject(BlockBitmaps[i]);
    }
}

void DrawBlock(BoardPoint point) {
    HDC hDC = GetDC(hWnd);
    BYTE BlockValue = ACCESS_BLOCK(point) & BLOCK_STATE_MASK;
    BitBlt(hDC, point.Column * 16 - 4, point.Row * 16 + 39, BLOCK_WIDTH, BLOCK_HEIGHT, BlockStates[BlockValue], 0, 0, SRCCOPY);
    ReleaseDC(hWnd, hDC);
}



void DisplaySmile(DWORD smileId) {
    HDC hDC = GetDC(hWnd);
    DisplaySmileOnDC(hDC, smileId);
    ReleaseDC(hWnd, hDC);
}


void DisplaySmileOnDC(HDC hDC, DWORD smileId) {
    SetDIBitsToDevice(
        hDC, // hdc
        (xRight - 24) / 2, // x
        16, // y
        24, // w
        24, // h
        0, // xSrc
        0, // ySrc 
        0, // ScanStart
        24, // cLines
        SmileBitmapIndex[smileId] + lpSmilesBitmapInfo, // lpvBits
        lpSmilesBitmapInfo, // lpbmi
        FALSE // ColorUse
    );
}

void DisplayTimerSeconds() {
    HDC hDC = GetDC(hWnd);
    DisplayTimerSecondsOnDC(hDC);
    ReleaseDC(hWnd, hDC);
}


void DisplayTimerSecondsOnDC(HDC hDC) {

    DWORD layout = GetLayout(hDC);

    if (layout & 1) {
        SetLayout(hDC, 0);
    }

    // Largest Digit
    DisplayNumber(hDC, xRight - WindowWidthInPixels - 56, TimerSeconds / 100);

    // Second Digit
    DisplayNumber(hDC, xRight - WindowWidthInPixels - 43, TimerSeconds / 10);

    // Last Digit
    DisplayNumber(hDC, xRight - WindowWidthInPixels - 30, TimerSeconds % 10);

    if (layout & 1) {
        SetLayout(hDC, layout);
    }
}

void DisplayAllBlocks() {
    HDC hDC = GetDC(hWnd);
    DisplayAllBlocksInDC(hDC);
    ReleaseDC(hWnd, hDC);
}

void DisplayAllBlocksInDC(HDC hDC) {
    int y = 55;

    for (int loop_row = 1; loop_row <= Height; ++loop_row) {
        int x = 12;

        for (int loop_column = 1; loop_column <= Width; loop_column++) {
            // Get the current state of the block
            BYTE blockValue = BlockArray[loop_row][loop_column];
            HDC blockState = BlockStates[blockValue & BLOCK_STATE_MASK];

            // Draw the block
            BitBlt(hDC, x, y, 16, 16, blockState, 0, 0, SRCCOPY);
            x += 16;
        }

        y += 16;
    }
}

void RedrawUI() {
    HDC hDC = GetDC(hWnd);
    RedrawUIOnDC(hDC);
    ReleaseDC(hWnd, hDC);
}

void RedrawUIOnDC(HDC hDC) {
    DrawHUDRectangles(hDC);
    DisplayLeftFlagsOnDC(hDC);
    DisplaySmileOnDC(hDC, GlobalSmileId);
    DisplayTimerSecondsOnDC(hDC);
    DisplayAllBlocksInDC(hDC);
}

void DrawHUDRectangles(HDC hDC) {
    RECT rect;

    // Draw Frame Bar
    // Does not use the lower-right lines
    rect.left = 0;
    rect.top = 0;
    rect.right = xRight - 1;
    rect.bottom = yBottom - 1;
    DrawHUDRectangle(hDC, rect, 3, 1);

    //  Blocks Board Rectangle
    rect.left = 9;
    rect.top = 52;
    rect.right = xRight - 10;
    rect.bottom = yBottom - 1 - 9;
    DrawHUDRectangle(hDC, rect, 3, 1);

    // Upper Rectangle - Contains: LeftMines | Smile | SecondsLeft
    rect.left = 9;
    rect.top = 9;
    rect.right = xRight - 10;
    rect.bottom = 45;
    DrawHUDRectangle(hDC, rect, 2, 0);

    // LeftMines Counter Rectangle
    rect.left = 16;
    rect.top = 16;
    rect.right = 56;
    rect.bottom = 39;
    DrawHUDRectangle(hDC, rect, 1, 0);

    // SecondsLeft Rectangle
    rect.left = xRight - WindowWidthInPixels - 57;
    rect.top = 15;
    rect.right = rect.left + 40;
    rect.bottom = 39;
    DrawHUDRectangle(hDC, rect, 1, 0);

    // Smile Rectangle
    rect.left = (xRight - 24) / 2 - 1;
    rect.top = 15;
    rect.right = rect.left + 25;
    rect.bottom = 40;
    DrawHUDRectangle(hDC, rect, 1, 2);
}


void SetROPWrapper(HDC hDC, BYTE white_or_copypen) {
    if (white_or_copypen & 1) {
        SetROP2(hDC, R2_WHITE);
    }
    else {
        SetROP2(hDC, R2_COPYPEN);
        SelectObject(hDC, hPen);
    }
}

/*
If white_or_copypen is 1, the lower-right side is not drawn
*/
void DrawHUDRectangle(HDC hDC, RECT rect, int lines_width, char white_or_copypen) {

    SetROPWrapper(hDC, white_or_copypen);

    for (int i = 0; i < lines_width; i++) {
        rect.bottom--;
        MoveToEx(hDC, rect.left, rect.bottom, NULL);

        // Draw left vertical line
        LineTo(hDC, rect.left, rect.top);
        rect.left++;

        // Draw top line
        LineTo(hDC, rect.right, rect.top);
        rect.right--;
        rect.top++;
    }

    if (white_or_copypen < 2) {
        SetROPWrapper(hDC, white_or_copypen ^ 1);
    }

    for (int i = 0; i < lines_width; i++) {
        rect.bottom++;
        MoveToEx(hDC, rect.left, rect.bottom, NULL);
        rect.left--;
        rect.right++;

        // Draw lower line
        LineTo(hDC, rect.right, rect.right);
        rect.top--;

        // Draw right line
        LineTo(hDC, rect.right, rect.top);
    }
}

int GetBitmapByteLength(int a, int b) {
    int colorDepth = (GameConfig.Color) ? 4 : 1;
    colorDepth = (colorDepth * a + 31) / 8;
    // Clear those bits: 0b11
    colorDepth &= ~0b11;
    return colorDepth * b;
}

