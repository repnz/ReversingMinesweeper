#include "registry.h"
#include "resource.h"

HKEY hRegistryKey;

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

// .text: 1002B80
VOID LoadValue(RegistryValue id, LPWSTR lpData) {
    LPCWSTR lpValueName = RegistryValuesNames[(DWORD)id];
    DWORD cbData = 64;
    
    if (RegQueryValueExW(
        hRegistryKey, 
        lpValueName,  
        NULL,         
        NULL, 
        (LPBYTE)lpData, 
        &cbData)  != 0) {

        lstrcpyW(lpData, AnonymousStr);

    }
}

// .text: 
int GetIntegerFromRegistry(RegistryValue regValue, int defaultValue, int minValue, int maxValue) {
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