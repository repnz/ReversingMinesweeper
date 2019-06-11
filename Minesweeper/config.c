#include "config.h"
#include "resource.h"

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

// .data: 01005AE0
WCHAR SecondsLeftBuffer[32];
WCHAR AnonymousStr[32];

void SaveConfigToRegistry() {
    DWORD dwDisposition;
    RegCreateKeyExW(HKEY_CURRENT_USER, lpSubKey, 0, 0, 0, KEY_WRITE, 0, &hRegistryKey, &dwDisposition);

    SetIntegerInRegistry(Difficulty, GameConfig.Difficulty);
    SetIntegerInRegistry(Height, GameConfig.Height);
    SetIntegerInRegistry(Width, GameConfig.Width);
    SetIntegerInRegistry(Mines, GameConfig.Mines);
    SetIntegerInRegistry(Mark, GameConfig.Mark);
    SetIntegerInRegistry(AlreadyPlayed, TRUE);
    SetIntegerInRegistry(Color, GameConfig.Color);
    SetIntegerInRegistry(Sound, GameConfig.Sound);
    SetIntegerInRegistry(Xpos, GameConfig.Xpos);
    SetIntegerInRegistry(Ypos, GameConfig.Ypos);
    SetIntegerInRegistry(Time1, GameConfig.Times[0]);
    SetIntegerInRegistry(Time2, GameConfig.Times[1]);
    SetIntegerInRegistry(Time3, GameConfig.Times[2]);

    SetStringInRegistry(Name1, GameConfig.Names[0]);
    SetStringInRegistry(Name2, GameConfig.Names[1]);
    SetStringInRegistry(BestExpertName, GameConfig.Names[2]);

    RegCloseKey(hRegistryKey);
}

void SetStringInRegistry(ConfigItem regValue, LPCWSTR lpStringValue) {
    RegSetValueExW(
        HKEY_CURRENT_USER,
        RegistryValuesNames[(DWORD)regValue],
        0,
        REG_SZ,
        (PBYTE)lpStringValue,
        lstrlenW(lpStringValue)
    );
}

void SetIntegerInRegistry(ConfigItem regValue, DWORD value) {
    RegSetValueExW(
        HKEY_CURRENT_USER,
        RegistryValuesNames[(DWORD)regValue],
        0,
        REG_DWORD,
        (PBYTE)&value,
        sizeof(DWORD)
    );
}

VOID GetStringFromRegistry(ConfigItem id, LPWSTR lpData) {
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

    RegCreateKeyExW(HKEY_CURRENT_USER, lpSubKey, 0, NULL, 0, KEY_READ, NULL, &hRegistryKey, &dwDisposition);

    GameConfig.Height = GetIntegerFromRegistry(Height, 9, 9, 25);
    Height = GameConfig.Height;
    GameConfig.Width = GetIntegerFromRegistry(Width, 9, 9, 25);
    Width = GameConfig.Width;
    GameConfig.Difficulty = GetIntegerFromRegistry(Difficulty, 0, 0, 3);
    GameConfig.Mines = GetIntegerFromRegistry(Mines, 10, 10, 999);
    GameConfig.Xpos = GetIntegerFromRegistry(Xpos, 80, 0, 1024);
    GameConfig.Ypos = GetIntegerFromRegistry(Ypos, 80, 0, 1024);
    GameConfig.Sound = GetIntegerFromRegistry(Sound, 0, 0, 3);
    GameConfig.Mark = GetIntegerFromRegistry(Mark, 1, 0, 1);
    GameConfig.Tick = GetIntegerFromRegistry(Tick, 0, 0, 1);
    GameConfig.Menu = GetIntegerFromRegistry(Menu, 0, 0, 2);
    GameConfig.Times[TIME_BEGINNER] = GetIntegerFromRegistry(Time1, 999, 0, 999);
    GameConfig.Times[TIME_INTERMIDIATE] = GetIntegerFromRegistry(Time2, 999, 0, 999);
    GameConfig.Times[TIME_EXPERT] = GetIntegerFromRegistry(Time3, 999, 0, 999);

    GetStringFromRegistry(Name1, GameConfig.Names[0]);
    GetStringFromRegistry(Name2, GameConfig.Names[1]);
    GetStringFromRegistry(BestExpertName, GameConfig.Names[2]);

    HDC hDC = GetDC(GetDesktopWindow());

    int desktopColors = GetDeviceCaps(hDC, NUMCOLORS);
    GameConfig.Color = GetIntegerFromInitFile(Color, (desktopColors == 2) ? 0 : 1, 0, 1);

    ReleaseDC(GetDesktopWindow(), hDC);

    if (GameConfig.Sound == 3) {
        GameConfig.Sound = StopAllSound();
    }

    RegCloseKey(hRegistryKey);

}

// .text: 
int GetIntegerFromRegistry(ConfigItem regValue, int defaultValue, int minValue, int maxValue) {
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
int GetIntegerFromInitFile(ConfigItem regValue, int nDefault, int minValue, int maxValue) {

    LPCWSTR lpKeyName = RegistryValuesNames[(DWORD)regValue];

    return max(min(maxValue, GetPrivateProfileIntW(ClassName, lpKeyName, nDefault, lpInitFileName)), minValue);
}

int GetStringFromInitFile(ConfigItem regValue, LPWSTR lpReturnedString) {
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

    if (RegCreateKeyExW(HKEY_CURRENT_USER, lpSubKey, 0, NULL,
        0, KEY_READ, NULL, &hRegistryKey, &dwDisposition) != ERROR_SUCCESS) {
        return;
    }

    //
    // Check If The Player Already Played
    //
    int alreadyPlayed = GetIntegerFromRegistry(AlreadyPlayed, 0, 0, 1);

    RegCloseKey(hRegistryKey);

    if (alreadyPlayed) {
        return;
    }

    // Load Items From .ini File
    GameConfig.Height = GetIntegerFromInitFile(Height, 9, 9, 25);
    GameConfig.Width = GetIntegerFromInitFile(Width, 9, 9, 30);
    GameConfig.Difficulty = GetIntegerFromInitFile(Difficulty, 0, 0, 3);
    GameConfig.Mines = GetIntegerFromInitFile(Mines, 10, 10, 999);
    GameConfig.Xpos = GetIntegerFromInitFile(Xpos, 80, 0, 1024);
    GameConfig.Ypos = GetIntegerFromInitFile(Ypos, 80, 0, 1024);
    GameConfig.Sound = GetIntegerFromInitFile(Sound, 0, 0, 3);
    GameConfig.Mark = GetIntegerFromInitFile(Mark, 1, 0, 1);
    GameConfig.Tick = GetIntegerFromInitFile(Tick, 0, 0, 1);
    GameConfig.Menu = GetIntegerFromInitFile(Menu, 0, 0, 2);
    GameConfig.Times[TIME_BEGINNER] = GetIntegerFromInitFile(Time1, 999, 0, 999);
    GameConfig.Times[TIME_INTERMIDIATE] = GetIntegerFromInitFile(Time2, 999, 0, 999);
    GameConfig.Times[TIME_EXPERT] = GetIntegerFromInitFile(Time3, 999, 0, 999);

    GetStringFromInitFile(Name1, GameConfig.Names[0]);
    GetStringFromInitFile(Name2, GameConfig.Names[1]);
    GetStringFromInitFile(BestExpertName, GameConfig.Names[2]);

    HDC hDC = GetDC(GetDesktopWindow());
    int desktopColors = GetDeviceCaps(hDC, NUMCOLORS);
    GameConfig.Color = GetIntegerFromInitFile(Color, (desktopColors == 2) ? FALSE : TRUE, 0, 1);
    ReleaseDC(GetDesktopWindow(), hDC);

    if (GameConfig.Sound == 3) {
        GameConfig.Sound = StopAllSound();
    }
}