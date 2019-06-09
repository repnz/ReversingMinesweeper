#pragma once
#include <Windows.h>

// Windowing Functions
BOOL HandleLeftClick(DWORD dwLocation);
void InitializeCheckedMenuItems();
INT_PTR CALLBACK CustomFieldDialogProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK SaveWinnerNameDialogProc(HWND hDialog, UINT uMsg, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK WinnersDialogProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
void SaveWinnerNameDialogBox();
DWORD SimpleGetSystemMetrics(DWORD val);
void InitializeWindowBorder(DWORD flags);
void CustomFieldDialogBox();
void ShowWinnerNameAndTime(HWND hDlg, int nIDDlgItem, int secondsLeft, LPCWSTR lpName);
void WinnersDialogBox();
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
__inline BOOL MenuHandler(WORD menuItem);
__inline void KeyDownHandler(WPARAM wParam);
__inline LRESULT CaptureMouseInput(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
__inline LRESULT MouseMoveHandler(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);

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
void DrawHUDRectangle(HDC hDC, RECT rect, DWORD lines_width, BYTE white_or_copypen);
void DrawHUDRectangles(HDC hDC);
void RedrawUIOnDC(HDC hDC);
void RedrawUI();
BOOL InitializeBitmapsAndBlockArray();


// Registry Functions
int GetIntegerFromRegistry(RegistryValue regValue, int defaultValue, int minValue, int maxValue);
VOID GetStringFromRegistry(RegistryValue id, LPWSTR lpData);
void InitializeConfigFromRegistry();
void SetIntegerInRegistry(RegistryValue regValue, DWORD value);
void SetStringInRegistry(RegistryValue regValue, LPCWSTR lpStringValue);
void SaveConfigToRegistry();

// Board Functions
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

// Sound Functions
DWORD StopAllSound();
void FreeSound();
void PlayGameSound(DWORD soundType);

// Misc
int GetRandom(DWORD maxValue);
void DisplayErrorMessage(UINT uID);
VOID LoadResourceString(UINT uID, LPWSTR lpBuffer, DWORD cchBufferMax);

// Init File Functions
int GetIntegerFromInitFile(RegistryValue regValue, int nDefault, DWORD minValue, DWORD maxValue);
int GetStringFromInitFile(RegistryValue regValue, LPWSTR lpReturnedString);
void InitMetricsAndFirstGame();

// Menu Functions
void SetMenuItemState(DWORD uID, BOOL isChecked);
void InitializeMenu(DWORD menuFlags);

// Help Window Functions
void ShowAboutWindow();
void ShowHelpHtml(DWORD arg0, UINT uCommand);
// ??
int GetDlgIntOfRange(HWND hDlg, int nIDDlgItem, int min, int max);
void DisplayHelpWindow(HWND hDesktopWnd, LPCSTR lpChmFilename, UINT uCommand, DWORD_PTR dwData);
BOOL FindHtmlHelpDLL(PSTR outputLibraryName);