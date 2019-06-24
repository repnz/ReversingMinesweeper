#include <Windows.h>
#include "windowing.h"
#include "resource.h"

int GetRandom(DWORD maxValue) {
    return rand() % maxValue;
}

// .text:01003950
void DisplayErrorMessage(UINT uID) {
    WCHAR Buffer[128];
    WCHAR Caption[128];

    if (uID >= 999) {
        LoadStringW(hModule, ID_ERR_MSG_D, Caption, sizeof(Caption));
        wsprintfW(Buffer, Caption, uID);
    }
    else {
        LoadStringW(hModule, uID, Buffer, sizeof(Buffer));
    }

    // Show Title: Minesweeper Error, Content: Buffer from above
    LoadStringW(hModule, ID_ERROR, Caption, sizeof(Caption));
    MessageBoxW(NULL, Buffer, Caption, MB_ICONERROR);
}

VOID LoadResourceString(UINT uID, LPWSTR lpBuffer, DWORD cchBufferMax) {
    if (!LoadStringW(hModule, uID, lpBuffer, cchBufferMax)) {
        DisplayErrorMessage(1001);
    }
}
