#include "config.h"

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

	SetIntegerInRegistry(Difficulty, Difficulty_InitFile);
	SetIntegerInRegistry(Height, Height_InitFile);
	SetIntegerInRegistry(Width, Width_InitFile);
	SetIntegerInRegistry(Mines, Mines_InitFile);
	SetIntegerInRegistry(Mark, Mark_InitFile);
	SetIntegerInRegistry(AlreadyPlayed, TRUE);
	SetIntegerInRegistry(Color, Color_InitFile);
	SetIntegerInRegistry(Sound, Sound_InitFile);
	SetIntegerInRegistry(Xpos, Xpos_InitFile);
	SetIntegerInRegistry(Ypos, Ypos_InitFile);
	SetIntegerInRegistry(Time1, Time_InitFile[0]);
	SetIntegerInRegistry(Time2, Time_InitFile[1]);
	SetIntegerInRegistry(Time3, Time_InitFile[2]);

	SetStringInRegistry(Name1, Name1_InitFile);
	SetStringInRegistry(Name2, Name2_InitFile);
	SetStringInRegistry(BestExpertName, Name3_InitFile);

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

	Height_InitFile = GetIntegerFromRegistry(Height, 9, 9, 25);
	Height_InitFile2 = Height_InitFile;
	Width_InitFile = GetIntegerFromRegistry(Width, 9, 9, 25);
	Width_InitFile2 = Width_InitFile;
	Difficulty_InitFile = GetIntegerFromRegistry(Difficulty, 0, 0, 3);
	Mines_InitFile = GetIntegerFromRegistry(Mines, 10, 10, 999);
	Xpos_InitFile = GetIntegerFromRegistry(Xpos, 80, 0, 1024);
	Ypos_InitFile = GetIntegerFromRegistry(Ypos, 80, 0, 1024);
	Sound_InitFile = GetIntegerFromRegistry(Sound, 0, 0, 3);
	Mark_InitFile = GetIntegerFromRegistry(Mark, 1, 0, 1);
	Tick_InitFile = GetIntegerFromRegistry(Tick, 0, 0, 1);
	Menu_InitFile = GetIntegerFromRegistry(Menu, 0, 0, 2);
	Time_InitFile[TIME_BEGINNER] = GetIntegerFromRegistry(Time1, 999, 0, 999);
	Time_InitFile[TIME_INTERMIDIATE] = GetIntegerFromRegistry(Time2, 999, 0, 999);
	Time_InitFile[TIME_EXPERT] = GetIntegerFromRegistry(Time3, 999, 0, 999);

	GetStringFromRegistry(Name1, Name1_InitFile);
	GetStringFromRegistry(Name2, Name2_InitFile);
	GetStringFromRegistry(BestExpertName, Name3_InitFile);

	HDC hDC = GetDC(GetDesktopWindow());

	int desktopColors = GetDeviceCaps(hDC, NUMCOLORS);
	Color_InitFile = GetIntegerFromInitFile(Color, (desktopColors == 2) ? 0 : 1, 0, 1);

	ReleaseDC(GetDesktopWindow(), hDC);

	if (Sound_InitFile == 3) {
		Sound_InitFile = StopAllSound();
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
int GetIntegerFromInitFile(ConfigItem regValue, int nDefault, DWORD minValue, DWORD maxValue) {

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
	Height_InitFile = GetIntegerFromInitFile(Height, 9, 9, 25);
	Width_InitFile = GetIntegerFromInitFile(Width, 9, 9, 30);
	Difficulty_InitFile = GetIntegerFromInitFile(Difficulty, 0, 0, 3);
	Mines_InitFile = GetIntegerFromInitFile(Mines, 10, 10, 999);
	Xpos_InitFile = GetIntegerFromInitFile(Xpos, 80, 0, 1024);
	Ypos_InitFile = GetIntegerFromInitFile(Ypos, 80, 0, 1024);
	Sound_InitFile = GetIntegerFromInitFile(Sound, 0, 0, 3);
	Mark_InitFile = GetIntegerFromInitFile(Mark, 1, 0, 1);
	Tick_InitFile = GetIntegerFromInitFile(Tick, 0, 0, 1);
	Menu_InitFile = GetIntegerFromInitFile(Menu, 0, 0, 2);
	Time_InitFile[TIME_BEGINNER] = GetIntegerFromInitFile(Time1, 999, 0, 999);
	Time_InitFile[TIME_INTERMIDIATE] = GetIntegerFromInitFile(Time2, 999, 0, 999);
	Time_InitFile[TIME_EXPERT] = GetIntegerFromInitFile(Time3, 999, 0, 999);

	GetStringFromInitFile(Name1, Name1_InitFile);
	GetStringFromInitFile(Name2, Name2_InitFile);
	GetStringFromInitFile(BestExpertName, Name3_InitFile);

	HDC hDC = GetDC(GetDesktopWindow());
	int desktopColors = GetDeviceCaps(hDC, NUMCOLORS);
	Color_InitFile = GetIntegerFromInitFile(Color, (desktopColors == 2) ? FALSE : TRUE, 0, 1);
	ReleaseDC(GetDesktopWindow(), hDC);

	if (Sound_InitFile == 3) {
		Sound_InitFile = StopAllSound();
	}
}