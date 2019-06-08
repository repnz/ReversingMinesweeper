#pragma once
#include <Windows.h>

void DrawHUDRectangles(HDC hDC);
void TickSeconds();
BOOL LoadBitmaps();
void DrawHUDRectangle(HDC hDC, RECT rect, DWORD lines_width, BYTE white_or_copypen);
int CountNearBombs(BoardPoint point);
void FinishGame(BOOL isWon);
void ShowAboutWindow();
void ShowBlockValue(BoardPoint point);
BOOL FindHtmlHelpDLL(PSTR outputLibraryName);
void DisplayHelpWindow(HWND hDesktopWnd, LPCSTR lpChmFilename, UINT uCommand, DWORD_PTR dwData);
void DisplayNumber(HDC hDC, int xPosition, int numberToDisplay);
void ShowHelpHtml(DWORD arg0, UINT uCommand);
int GetDlgIntOfRange(HWND hDlg, int nIDDlgItem, int min, int max);
void RevealAllBombs(BYTE revealedBombsState);
void DisplayAllBlocks();
void DisplayAllBlocksInDC(HDC hDC);
void SaveWinnerNameDialogBox();
INT_PTR CALLBACK SaveWinnerNameDialogProc(HWND hDialog, UINT uMsg, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK WinnersDialogProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
void ShowWinnerNameAndTime(HWND hDlg, int nIDDlgItem, int secondsLeft, LPCWSTR lpName);
__inline void KeyDownHandler(WPARAM wParam);
void HandleRightClick(BoardPoint point);
void WinnersDialogBox();
DWORD GetFlagBlocksCount(BoardPoint point);
void DisplayTimerSeconds();
void DisplayTimerSecondsOnDC(HDC hDC);
void PlayGameSound(DWORD soundType);
DWORD StopAllSound();
__inline BOOL IsInBoardRange(BoardPoint point);
__inline VOID UpdateClickedBlocksStateNormal(BoardPoint point, BoardPoint oldClick);
void UpdateClickedBlocksState(BoardPoint point);
void UpdateBlockStateToClicked(BoardPoint point);
void UpdateBlockStateToUnclicked(BoardPoint point);
void DrawBlock(BoardPoint point);
BOOL HandleLeftClick(DWORD dwLocation);
void DisplaySmile(DWORD smileId);
void DisplaySmileOnDC(HDC hDC, DWORD smileId);
void InitializeMenu(DWORD menuFlags);
__inline BOOL MenuHandler(WORD menuItem);
void InitializeNewGame();
void InitializeCheckedMenuItems();
void ChangeBlockState(BoardPoint point, BYTE blockState);
void SetMenuItemState(DWORD uID, BOOL isChecked);
void SaveConfigToRegistry();
void SetStringInRegistry(RegistryValue regValue, LPCWSTR lpStringValue);
void SetIntegerInRegistry(RegistryValue regValue, DWORD value);
void FreePenAndBlocksAndSound();
void FreePenAndBlocks();
void FreeSound();
__inline LRESULT CaptureMouseInput(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
__inline LRESULT MouseMoveHandler(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
HRSRC FindBitmapResource(USHORT resourceId);
__inline BOOL LoadBitmapResources();
void DisplayResult();
void AddAndDisplayLeftFlags(DWORD leftFlagsToAdd);
void NotifyMinimize();
void DisplayLeftFlags();
void DisplayLeftFlagsOnDC(HDC hDC);
void ExpandEmptyBlock(BoardPoint point);
void HandleBlockClick(BoardPoint point);
int GetRandom(DWORD maxValue);
void NotifyWindowRestore();
void RedrawUIOnDC(HDC hDC);
void RedrawUI();
void CustomFieldDialogBox();
void Handle3x3Click(BoardPoint point);
__inline void InitializeBitmapsIndexes();
__inline void InitializePen();
__inline void ProcessBlockBitmaps();
void InitializeWindowBorder(DWORD flags);
void InitializeBlockArrayBorders();
__inline HGLOBAL TryLoadBitmapResource(USHORT resourceId);
__inline void ReleaseBlocksClick();
void InitializeConfigFromRegistry();
__inline void InitializeBitmapIndexes(PDWORD indexesArray, int numberOfBitmaps, DWORD firstBitmapIndex, DWORD bytesPerBitmap);
BOOL InitializeBitmapsAndBlockArray();
int GetIntegerFromInitFile(RegistryValue regValue, int nDefault, DWORD minValue, DWORD maxValue);
int GetBitmapByteLength(int a, int b);
int GetStringFromInitFile(RegistryValue regValue, LPWSTR lpReturnedString);