#pragma once
#include <Windows.h>

HGLOBAL hBlocksBitmapResource;
HGLOBAL hSmilesBitmapResource;
HGLOBAL hNumbersBitmapResource;
HPEN hPen;
PBITMAPINFO lpBlocksBitmapInfo;
PBITMAPINFO lpNumbersBitmapInfo;
PBITMAPINFO lpSmilesBitmapInfo;

DWORD BlockBitmapIndex[16];
DWORD NumberBitmapIndex[12];
DWORD SmileBitmapIndex[5];

HBITMAP BlockBitmaps[16];

 BYTE BlockArray[27][32];

#define ACCESS_BLOCK(point) (BlockArray[point.Row][point.Column])


 typedef struct _BOARD_POINT {
	 DWORD Column;
	 DWORD Row;
 } BoardPoint;


int GlobalSmileId;
int Mines_Copy;
DWORD TimerSeconds;
DWORD NumberOfRevealedBlocks;
DWORD NumberOfEmptyBlocks;


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

DWORD StateFlags = STATE_GAME_FINISHED | STATE_WINDOW_MINIMIZED;
int LeftFlags;

HelpEntry winnersHelpData[] = {
    { ID_DIALOG_WINNERS_BTN_RESET_SCORES, 1003},
    { 709, 1004},
    { 710, 1004},
    { 701, 1004},
    { 703, 1004},
    { 705, 1004},
    { 702, 1004},
    { 704, 1004},
    { 706, 1004}
};

BOOL NeedToSaveConfigToRegistry;

typedef HWND(*HTMLHELPWPROC)(
    HWND hwndCaller,
    LPCWSTR pszFile,
    UINT uCommand,
    DWORD_PTR dwData);

HMODULE HtmlHelpModuleHandle = NULL;
BOOL ErrorLoadingHelpFunc;
HTMLHELPWPROC HtmlHelpWPtr = NULL;

DWORD HelpValue = 0;

DWORD currentLocationIndex;

DWORD RowsList[100];
DWORD ColumnsList[100];

HelpEntry customFieldHelpData[] = {
    { ID_DIALOG_CUSTOM_FIELD_HEIGHT, 1000},
    { ID_DIALOG_CUSTOM_FIELD_WIDTH, 1001},
    { ID_DIALOG_CUSTOM_FIELD_MINES, 1002},
    { ID_DIALOG_CUSTOM_FIELD_HEIGHT_LABEL, 1000},
    { ID_DIALOG_CUSTOM_FIELD_WIDTH_LABEL, 1001},
    { ID_DIALOG_CUSTOM_FIELD_MINES_LABEL, 1002},
    { 0, 0}
};

BOOL IsTimerOnTemp;
BOOL IgnoreSingleClick;
BOOL IsMenuOpen;
BOOL Is3x3Click;

BoardPoint ClickedBlock;

DWORD HasMouseCapture;
DWORD CheatPasswordIndex;
WCHAR CheatPassword[] = L"XYZZY";

LPCWSTR lpInitFileName = L"entpack.ini";
LPCWSTR lpSubKey = L"Software\\Microsoft\\winmine";

HWND hWnd;
HINSTANCE hModule;
BOOL Minimized;
int ScreenHeightInPixels;
int MenuBarHeightInPixels;
int WindowHeightInPixels;
int WindowWidthInPixels;

short Difficulty_InitFile;
int Mines_InitFile;

// In Pixels, Screen Coordinates
int Xpos_InitFile;
int Ypos_InitFile;

// 0 -> there is no sound
// 1 -> ?
// 2 -> could not call SND_PURGE / called FreeSound
// 3 -> Sound is playing
int Sound_InitFile;
int Mark_InitFile;
int Menu_InitFile;
int Tick_InitFile;

#define TIME_BEGINNER 0
#define TIME_INTERMIDIATE 1
#define TIME_EXPERT 2

DWORD Time_InitFile[3];

BOOL Color_InitFile;

WCHAR Name1_InitFile[32];
WCHAR Name2_InitFile[32];
WCHAR Name3_InitFile[32];

HICON hIcon;
HMENU hMenu;

// TODO: What is the difference between those variables
// TODO: Make sure I did not confuse these variables
DWORD Width_InitFile2;
DWORD Height_InitFile2;
DWORD Height_InitFile;
DWORD Width_InitFile;

// Number of pixels in the window
int xRight = 0;
int yBottom = 0;

// If this is FALSE, timer does not display time progress
// After calling "FinishGame" the flag is FALSE
// Calling InitializeNewGame() sets this to FALSE?!
// Before calling SetTimer(), set this to TRUE
BOOL IsTimerOnAndShowed;

// .text: 1005B88
int WindowHeightIncludingMenu = 0;

// Indexes are block states
HDC BlockStates[16];