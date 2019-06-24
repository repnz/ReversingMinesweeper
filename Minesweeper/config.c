#include "config.h"
#include "utils.h"
#include "resource.h"
#include "game.h"
#include "windowing.h"
#include "sound.h"


Config GameConfig;

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

HKEY hRegistryKey;
// Registry Vars
BOOL NeedToSaveConfigToRegistry;

// Init File 
WCHAR lpInitFileName[] = L"entpack.ini";

PCWSTR RegistryKeyName = L"Software\\Microsoft\\winmine";

// .data: 01005AE0
WCHAR SecondsLeftBuffer[32];
WCHAR AnonymousStr[32];

// Private Functions
int GetIntegerFromRegistry(DWORD regValue, int defaultValue, int minValue, int maxValue);
VOID GetStringFromRegistry(DWORD id, LPWSTR lpData);
void SetIntegerInRegistry(DWORD regValue, DWORD value);
void SetStringInRegistry(DWORD regValue, LPCWSTR lpStringValue);
int GetIntegerFromInitFile(DWORD regValue, int nDefault, int minValue, int maxValue);
int GetStringFromInitFile(DWORD regValue, LPWSTR lpReturnedString);

void SaveConfigToRegistry() {
    DWORD dwDisposition;
    RegCreateKeyExW(HKEY_CURRENT_USER, RegistryKeyName, 0, 0, 0, KEY_WRITE, 0, &hRegistryKey, &dwDisposition);

    SetIntegerInRegistry(CONFIG_DIFFICULTY, GameConfig.Difficulty);
    SetIntegerInRegistry(CONFIG_HEIGHT, GameConfig.Height);
    SetIntegerInRegistry(CONFIG_WIDTH, GameConfig.Width);
    SetIntegerInRegistry(CONFIG_MINES, GameConfig.Mines);
    SetIntegerInRegistry(CONFIG_MARK, GameConfig.Mark);
    SetIntegerInRegistry(CONFIG_ALREADY_PLAYED, TRUE);
    SetIntegerInRegistry(CONFIG_COLOR, GameConfig.Color);
    SetIntegerInRegistry(CONFIG_SOUND, GameConfig.Sound);
    SetIntegerInRegistry(CONFIG_XPOS, GameConfig.Xpos);
    SetIntegerInRegistry(CONFIG_YPOS, GameConfig.Ypos);
    SetIntegerInRegistry(CONFIG_TIME1, GameConfig.Times[0]);
    SetIntegerInRegistry(CONFIG_TIME2, GameConfig.Times[1]);
    SetIntegerInRegistry(CONFIG_TIME3, GameConfig.Times[2]);

    SetStringInRegistry(CONFIG_NAME1, GameConfig.Names[0]);
    SetStringInRegistry(CONFIG_NAME2, GameConfig.Names[1]);
    SetStringInRegistry(CONFIG_NAME3, GameConfig.Names[2]);

    RegCloseKey(hRegistryKey);
}

void SetStringInRegistry(DWORD regValue, LPCWSTR lpStringValue) {
    RegSetValueExW(
        HKEY_CURRENT_USER,
        RegistryValuesNames[(DWORD)regValue],
        0,
        REG_SZ,
        (PBYTE)lpStringValue,
        lstrlenW(lpStringValue)
    );
}

void SetIntegerInRegistry(DWORD regValue, DWORD value) {
    RegSetValueExW(
        HKEY_CURRENT_USER,
        RegistryValuesNames[(DWORD)regValue],
        0,
        REG_DWORD,
        (PBYTE)&value,
        sizeof(DWORD)
    );
}

VOID GetStringFromRegistry(DWORD id, LPWSTR lpData) {
    BYTE cbData = 64;

    if (RegQueryValueExW(
        hRegistryKey,
        RegistryValuesNames[(int)id],
        NULL,
        NULL,
        &cbData,
        (LPDWORD)lpData
    )) {
        lstrcpyW(lpData, AnonymousStr);
    }
}

void InitializeConfigFromRegistry() {
    DWORD dwDisposition;

    RegCreateKeyExW(HKEY_CURRENT_USER, RegistryKeyName, 0, NULL, 0, KEY_READ, NULL, &hRegistryKey, &dwDisposition);

    GameConfig.Height = GetIntegerFromRegistry(CONFIG_HEIGHT, 9, 9, 25);
    Height = GameConfig.Height;
    GameConfig.Width = GetIntegerFromRegistry(CONFIG_WIDTH, 9, 9, 25);
    Width = GameConfig.Width;
    GameConfig.Difficulty = GetIntegerFromRegistry(CONFIG_DIFFICULTY, 0, 0, 3);
    GameConfig.Mines = GetIntegerFromRegistry(CONFIG_MINES, 10, 10, 999);
    GameConfig.Xpos = GetIntegerFromRegistry(CONFIG_XPOS, 80, 0, 1024);
    GameConfig.Ypos = GetIntegerFromRegistry(CONFIG_YPOS, 80, 0, 1024);
    GameConfig.Sound = GetIntegerFromRegistry(CONFIG_SOUND, 0, 0, 3);
    GameConfig.Mark = GetIntegerFromRegistry(CONFIG_MARK, 1, 0, 1);
    GameConfig.Tick = GetIntegerFromRegistry(CONFIG_TICK, 0, 0, 1);
    GameConfig.Menu = GetIntegerFromRegistry(CONFIG_MENU, 0, 0, 2);
    GameConfig.Times[TIME_BEGINNER] = GetIntegerFromRegistry(CONFIG_TIME1, 999, 0, 999);
    GameConfig.Times[TIME_INTERMIDIATE] = GetIntegerFromRegistry(CONFIG_TIME2, 999, 0, 999);
    GameConfig.Times[TIME_EXPERT] = GetIntegerFromRegistry(CONFIG_TIME3, 999, 0, 999);

    GetStringFromRegistry(CONFIG_NAME1, GameConfig.Names[0]);
    GetStringFromRegistry(CONFIG_NAME2, GameConfig.Names[1]);
    GetStringFromRegistry(CONFIG_NAME3, GameConfig.Names[2]);

    HDC hDC = GetDC(GetDesktopWindow());

    int desktopColors = GetDeviceCaps(hDC, NUMCOLORS);
    GameConfig.Color = GetIntegerFromInitFile(CONFIG_COLOR, (desktopColors == 2) ? 0 : 1, 0, 1);

    ReleaseDC(GetDesktopWindow(), hDC);

    if (GameConfig.Sound == 3) {
        GameConfig.Sound = StopAllSound();
    }

    RegCloseKey(hRegistryKey);

}

// .text: 
int GetIntegerFromRegistry(DWORD regValue, int defaultValue, int minValue, int maxValue) {
    DWORD cbData = 4;
    int Data;

    if (!RegQueryValueExW(hRegistryKey, RegistryValuesNames[(DWORD)regValue], NULL, NULL, (LPBYTE)&Data, &cbData)) {
        return defaultValue;
    }

    if (min(maxValue, Data) < minValue) {
        return minValue;
    }

    if (maxValue < Data) {
        return maxValue;
    }

    return Data;
}



// In the assembly code there are many calls to GetPrivateProfileIntW(). 
// It is because it is called inside a macro argument.
// Moreover, the "min" logic is calculated twice, again because it's called inside a macro argument.
int GetIntegerFromInitFile(DWORD regValue, int nDefault, int minValue, int maxValue) {

    LPCWSTR lpKeyName = RegistryValuesNames[regValue];

    // Don't do this in real code plz unless max and min are inlined functions
    return max(
        min(maxValue, (int)GetPrivateProfileIntW(ClassName, lpKeyName, nDefault, lpInitFileName)),
        minValue
    );
}

int GetStringFromInitFile(DWORD regValue, LPWSTR lpReturnedString) {
    return GetPrivateProfileStringW(ClassName, RegistryValuesNames[(DWORD)regValue],
        AnonymousStr, lpReturnedString, 32, lpInitFileName);
}


void InitMetricsAndFirstGame() {

    //
    // Initialize The Random Seed
    //
    srand(GetTickCount());

    //
    // Load Strings From Resource Table
    //
    LoadResourceString(ID_MINESWEEPER_CLASSNAME, ClassName, sizeof(ClassName) / sizeof(WCHAR));
    LoadResourceString(ID_SECONDS_LEFT, SecondsLeftBuffer, sizeof(SecondsLeftBuffer) / sizeof(WCHAR));
    LoadResourceString(ID_ANONYMOUS, AnonymousStr, sizeof(AnonymousStr) / sizeof(WCHAR));

    ScreenHeightInPixels = GetSystemMetrics(SM_CYCAPTION) + 1;
    MenuBarHeightInPixels = GetSystemMetrics(SM_CYMENU) + 1;
    WindowHeightInPixels = GetSystemMetrics(SM_CYBORDER) + 1;
    WindowWidthInPixels = GetSystemMetrics(SM_CXBORDER) + 1;

    DWORD dwDisposition;

    if (RegCreateKeyExW(HKEY_CURRENT_USER, RegistryKeyName, 0, NULL,
        0, KEY_READ, NULL, &hRegistryKey, &dwDisposition) != ERROR_SUCCESS) {
        return;
    }

    //
    // Check If The Player Already Played
    //
    BOOL alreadyPlayed = GetIntegerFromRegistry(CONFIG_ALREADY_PLAYED, 0, 0, 1);

    RegCloseKey(hRegistryKey);

    if (alreadyPlayed) {
        return;
    }

    // Load Items From .ini File
    GameConfig.Height = GetIntegerFromInitFile(CONFIG_HEIGHT, 9, 9, 25);
    GameConfig.Width = GetIntegerFromInitFile(CONFIG_WIDTH, 9, 9, 30);
    GameConfig.Difficulty = GetIntegerFromInitFile(CONFIG_DIFFICULTY, 0, 0, 3);
    GameConfig.Mines = GetIntegerFromInitFile(CONFIG_MINES, 10, 10, 999);
    GameConfig.Xpos = GetIntegerFromInitFile(CONFIG_XPOS, 80, 0, 1024);
    GameConfig.Ypos = GetIntegerFromInitFile(CONFIG_YPOS, 80, 0, 1024);
    GameConfig.Sound = GetIntegerFromInitFile(CONFIG_SOUND, 0, 0, 3);
    GameConfig.Mark = GetIntegerFromInitFile(CONFIG_MARK, 1, 0, 1);
    GameConfig.Tick = GetIntegerFromInitFile(CONFIG_TICK, 0, 0, 1);
    GameConfig.Menu = GetIntegerFromInitFile(CONFIG_MENU, 0, 0, 2);
    GameConfig.Times[TIME_BEGINNER] = GetIntegerFromInitFile(CONFIG_TIME1, 999, 0, 999);
    GameConfig.Times[TIME_INTERMIDIATE] = GetIntegerFromInitFile(CONFIG_TIME2, 999, 0, 999);
    GameConfig.Times[TIME_EXPERT] = GetIntegerFromInitFile(CONFIG_TIME3, 999, 0, 999);

    GetStringFromInitFile(CONFIG_NAME1, GameConfig.Names[NAME_BEGINNER]);
    GetStringFromInitFile(CONFIG_NAME2, GameConfig.Names[NAME_INTERMIDIATE]);
    GetStringFromInitFile(CONFIG_NAME3, GameConfig.Names[NAME_EXPERT]);

    HDC hDC = GetDC(GetDesktopWindow());
    int desktopColors = GetDeviceCaps(hDC, NUMCOLORS);
    GameConfig.Color = GetIntegerFromInitFile(CONFIG_COLOR, (desktopColors == 2) ? FALSE : TRUE, 0, 1);
    ReleaseDC(GetDesktopWindow(), hDC);

    if (GameConfig.Sound == 3) {
        GameConfig.Sound = StopAllSound();
    }
}