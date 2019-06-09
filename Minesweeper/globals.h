#pragma once
#include <Windows.h>
#include "enums.h"

// Read Only Strings
const LPCWSTR winmineHelp = L"winmine.hlp";
const LPCWSTR lpSubKey = L"Software\\Microsoft\\winmine";

// Referenced in LoadBitmap()
const LPCSTR FailedToCreate = "Failed to create Bitmap\n";
const LPCSTR FailedToCreateDC = "FLoad failed to create compatible dc\n";

// Registry Strings:
//	- RegistryValues
//	- Registry SubKey
//

// Help.chm file


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
DWORD StateFlags = STATE_GAME_FINISHED | STATE_WINDOW_MINIMIZED;


DifficultyConfigItem DifficultyConfigTable[] = {
	{ BEGINNER_MINES, BEGINEER_HEIGHT, BEGINNER_WIDTH },
	{ INTERMIDIATE_MINES, INTERMIDIATE_HEIGHT, INTERMIDIATE_WIDTH },
	{ EXPERT_MINES, EXPERT_HEIGHT, EXPERT_WIDTH }
};

WCHAR CheatPassword[] = L"XYZZY";


HelpEntry customFieldHelpData[] = {
	{ ID_DIALOG_CUSTOM_FIELD_HEIGHT, 1000 },
	{ ID_DIALOG_CUSTOM_FIELD_WIDTH, 1001 },
	{ ID_DIALOG_CUSTOM_FIELD_MINES, 1002 },
	{ ID_DIALOG_CUSTOM_FIELD_HEIGHT_LABEL, 1000 },
	{ ID_DIALOG_CUSTOM_FIELD_WIDTH_LABEL, 1001 },
	{ ID_DIALOG_CUSTOM_FIELD_MINES_LABEL, 1002 },
	{ 0, 0 }
};

HelpEntry winnersHelpData[] = {
	{ ID_DIALOG_WINNERS_BTN_RESET_SCORES, 1003 },
	{ 709, 1004 },
	{ 710, 1004 },
	{ 701, 1004 },
	{ 703, 1004 },
	{ 705, 1004 },
	{ 702, 1004 },
	{ 704, 1004 },
	{ 706, 1004 }
};


// Registry Module Variables
LPCWSTR RegistryValuesNames[] = {
	L"Difficulty",
	L"Mines",
	L"Height",
	L"Width",
	L"Xpos",
	L"Ypos",
	L"Sound",
	L"Mark",
	L"Menu",
	L"Tick",
	L"Color",
	L"Time1",
	L"Name1",
	L"Time2",
	L"Name2",
	L"Time3",
	L"Name3",
	L"AlreadyPlayed"
};

// Board Variables
BoardPoint ClickedBlock = { -1, -1 };
LPCWSTR lpInitFileName[] = L"entpack.ini";

BOOL HasMouseCapture;
BOOL Is3x3Click;
BOOL IgnoreSingleClick;
BOOL IsMenuOpen;
DWORD CheatPasswordIndex;
HPEN hPen;
BOOL NeedToSaveConfigToRegistry;
int GlobalSmileId;


// If this is FALSE, timer does not display time progress
// After calling "FinishGame" the flag is FALSE
// Calling InitializeNewGame() sets this to FALSE
// Before calling SetTimer(), set this to TRUE
BOOL IsTimerOnAndShowed;
BOOL IsTimerOnTemp;
HMODULE HtmlHelpModuleHandle = NULL;
BOOL ErrorLoadingHelpFunc;

typedef HWND(*HTMLHELPWPROC)(
	HWND hwndCaller,
	LPCWSTR pszFile,
	UINT uCommand,
	DWORD_PTR dwData);



HTMLHELPWPROC HtmlHelpWPtr = NULL;
int LeftFlags;
DWORD ColumnsList[100];

int Mines_Copy;

// TODO: What is the difference between those variables
// TODO: Make sure I did not confuse these variables
DWORD Width_InitFile2;
DWORD Height_InitFile2;

BYTE BlockArray[27][32];

#define ACCESS_BLOCK(point) (BlockArray[point.Row][point.Column])

// --- Those variables here are in the same order of the strings array
//     It's logical that they are represented as structs
//
short Difficulty_InitFile;

int Mines_InitFile;

DWORD Height_InitFile;
DWORD Width_InitFile;

// In Pixels, Screen Coordinates
int Xpos_InitFile;
int Ypos_InitFile;

// 0 -> there is no sound
// 1 -> ?
// 2 -> could not call SND_PURGE / called FreeSound
// 3 -> Sound is playing
int Sound_InitFile;
int Mark_InitFile;
int Tick_InitFile;
int Menu_InitFile;
BOOL Color_InitFile;

#define TIME_BEGINNER 0
#define TIME_INTERMIDIATE 1
#define TIME_EXPERT 2

DWORD Time_InitFile[3];
WCHAR Name1_InitFile[32];
WCHAR Name2_InitFile[32];
WCHAR Name3_InitFile[32];
DWORD CurrentRowColumnListIndex;
DWORD TimerSeconds;
DWORD NumberOfEmptyBlocks;
DWORD NumberOfRevealedBlocks;
DWORD RowsList[100];
HKEY hRegistryKey;

// Bitmaps
HGLOBAL hSmilesBitmapResource;
HGLOBAL hBlocksBitmapResource;
PBITMAPINFO lpNumbersBitmapInfo;
DWORD SmileBitmapIndex[5];
HBITMAP BlockBitmaps[16];
DWORD BlockBitmapIndex[16];
PBITMAPINFO lpSmilesBitmapInfo;
PBITMAPINFO lpBlocksBitmapInfo;
HGLOBAL hNumbersBitmapResource;

// Indexes are block states
HDC BlockStates[16];
DWORD NumberBitmapIndex[12];

int WindowWidthInPixels;
HMENU hMenu;

// .data: 01005AA0
WCHAR ClassName[32];

// .data: 01005AE0
WCHAR SecondsLeftBuffer[32];
int yBottom = 0;
HWND hWnd;
HICON hIcon;
// Number of pixels in the window
int xRight = 0;
HINSTANCE hModule;
int MenuBarHeightInPixels;
// This variable is used only in WinMain
// To check if the window is minimized use "StateFlags" with STATE_WINDOW_MINIMIZED or STATE_WINDOW_MINIMIZED2
BOOL Minimized;
WCHAR AnonymousStr[32];
int ScreenHeightInPixels;
int WindowHeightInPixels;
int WindowHeightIncludingMenu = 0;




