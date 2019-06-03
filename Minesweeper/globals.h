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

// BYTE BlockArray[27][32];
BYTE BlockArray[864];

#define ACCESS_BLOCK(row, column) BlockArray[(row)*32+(column)]


int GlobalSmileId;
int Mines_Copy;
DWORD TimerSeconds;
DWORD NumberOfRevealedBlocks;
DWORD NumberOfEmptyBlocks;

// If game is finished, 16
// After initialization, 1
// Testing bits: 1, 8, 2
// Minimize Bits: 0xA. When restored, bits get turned off
// If 1 bit is not on, clicks are ignored
DWORD dword_1005000 = 0x18;
int CurrentPoints;

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
BOOL ErrorLoadingAll;
HTMLHELPWPROC HtmlHelpWPtr = NULL;

DWORD HelpValue = 0;

DWORD current_location_index;

DWORD RowsList[];
DWORD RowsList[];

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
DWORD ClickedBlockColumn;
DWORD ClickedBlockRow;

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

int Time_InitFile[3];

BOOL Color_InitFile;

WCHAR Name1_InitFile[32];
WCHAR Name2_InitFile[32];
WCHAR Name3_InitFile[32];

HICON hIcon;
HMENU hMenu;

// Number of blocks
int Width_InitFile2;
int Height_InitFile2;
int Height_InitFile;
int Width_InitFile;

// Number of pixels in the window
int xRight = 0;
int yBottom = 0;

// If this is FALSE, timer does not display time progress
// After calling "FinishGame" the flag is FALSE
// Calling InitializeMines() sets this to FALSE?!
// Before calling SetTimer(), set this to TRUE
BOOL IsTimerOnAndShowed;

// .text: 1005B88
int WindowHeightIncludingMenu = 0;

// Indexes are block states
HDC BlockStates[16];