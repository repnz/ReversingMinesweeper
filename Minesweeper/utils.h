#pragma once
#include <Windows.h>

// Misc
int GetRandom(DWORD maxValue);
void DisplayErrorMessage(UINT uID);
VOID LoadResourceString(UINT uID, LPWSTR lpBuffer, DWORD cchBufferMax);
