#pragma once
#include <Windows.h>

#define SMILE_NORMAL 0
#define SMILE_WOW    1
#define SMILE_LOST   2
#define SMILE_WINNER 3
#define SMILE_CLICKED 4

// Bitmap Drawing Functions
HRSRC FindBitmapResource(USHORT resourceId);
int GetBitmapByteLength(int a, int b);
BOOL LoadBitmaps();
__inline BOOL LoadBitmapResources();
__inline HGLOBAL TryLoadBitmapResource(USHORT resourceId);
__inline void InitializeBitmapsIndexes();
__inline void InitializeBitmapIndexes(PDWORD indexesArray, int numberOfBitmaps, DWORD firstBitmapIndex, DWORD bytesPerBitmap);
__inline void InitializePen();
__inline void ProcessBlockBitmaps();

void FreePenAndBlocks();
void FreePenAndBlocksAndSound();
void DrawBlock(BoardPoint point);
void DisplayAllBlocksInDC(HDC hDC);
void DisplayAllBlocks();
void DisplayNumber(HDC hDC, int xPosition, int numberToDisplay);
void DisplayLeftFlagsOnDC(HDC hDC);
void DisplayLeftFlags();
void DisplayTimerSecondsOnDC(HDC hDC);
void DisplayTimerSeconds();
void DisplaySmileOnDC(HDC hDC, DWORD smileId);
void DisplaySmile(DWORD smileId);
void SetROPWrapper(HDC hDC, BYTE white_or_copypen);
void DrawHUDRectangle(HDC hDC, RECT rect, int lines_width, char white_or_copypen);
void DrawHUDRectangles(HDC hDC);
void RedrawUIOnDC(HDC hDC);
void RedrawUI();