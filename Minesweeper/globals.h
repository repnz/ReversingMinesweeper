#pragma once

HGLOBAL hBlocksBitmapResource;
HGLOBAL hSmilesBitmapResource;
HGLOBAL hNumbersBitmapResource;
HPEN hPen;
PBITMAPINFO lpBlocksBitmapInfo;
PBITMAPINFO lpNumbersBitmapInfo;
PBITMAPINFO lpSmilesBitmapInfo;

DWORD dword_10059C0[16];
DWORD NumberBitmaps[12];
DWORD SmileBitmaps[5];

HBITMAP BlockBitmaps[16];

BYTE BlockArray[864];


int GlobalSmileId;
int Mines_Copy;
DWORD TimerSeconds;
DWORD NumberOfRevealedBlocks;
DWORD NumberOfEmptyBlocks;
DWORD dword_1005000;
int Mines_Copy2;

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

DWORD HelpValue;

DWORD current_location_index;

DWORD columns_array[];
DWORD rows_array[];

HelpEntry customFieldHelpData[] = {
    { ID_DIALOG_CUSTOM_FIELD_HEIGHT, 1000},
    { ID_DIALOG_CUSTOM_FIELD_WIDTH, 1001},
    { ID_DIALOG_CUSTOM_FIELD_MINES, 1002},
    { ID_DIALOG_CUSTOM_FIELD_HEIGHT_LABEL, 1000},
    { ID_DIALOG_CUSTOM_FIELD_WIDTH_LABEL, 1001},
    { ID_DIALOG_CUSTOM_FIELD_MINES_LABEL, 1002},
    { 0, 0}
};

DWORD dword_1005168;
DWORD dword_1005148;
DWORD dword_100514C;
DWORD dword_1005144;
DWORD ClickedBlockColumn;
DWORD ClickedBlockRow;

DWORD CheatValue1;
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

int Sound_InitFile;
int Mark_InitFile;
int Menu_InitFile;
int Tick_InitFile;

#define TIME_BEGINNER 0
#define TIME_INTERMIDIATE 1
#define TIME_EXPERT 2

int Time_InitFile[3];

int Color_InitFile;

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
DWORD dword_1005164;

// .text: 1005B88
int WindowHeightIncludingMenu = 0;

// Indexes are block states
HDC BlockStates[16];