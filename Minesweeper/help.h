#pragma once
#include <Windows.h>

// Help Window Functions
void ShowAboutWindow();
void ShowHelpHtml(DWORD arg0, UINT uCommand);
void DisplayHelpWindow(HWND hDesktopWnd, LPCSTR lpChmFilename, UINT uCommand, DWORD_PTR dwData);
BOOL FindHtmlHelpDLL(PSTR outputLibraryName);