#include "help.h"
#include "windowing.h"
#include "resource.h"
#include "config.h"

#define HtmlHelpW_ExportOrdinal 0x0E


// Help Module
HMODULE HtmlHelpModuleHandle = NULL;
BOOL ErrorLoadingHelpFunc;

typedef HWND(*HTMLHELPWPROC)(
    HWND hwndCaller,
    LPCWSTR pszFile,
    UINT uCommand,
    DWORD_PTR dwData
);



HTMLHELPWPROC HtmlHelpWPtr = NULL;

void ShowAboutWindow() {
    WCHAR szApp[128];
    WCHAR szCredits[128];

    LoadResourceString(ID_MINESWEEPER2, szApp, 128);
    LoadResourceString(ID_CREDITS, szCredits, 128);

    HICON hIcon = LoadIconW(hModule, (LPCWSTR)100);
    ShellAboutW(hWnd, szApp, szCredits, hIcon);
}

BOOL FindHtmlHelpDLL(PSTR outputLibraryName) {

    HKEY hKey;

    // This registry value actually contains the same ActiveX Control DLL "hhctrl.ocx"
    if (!RegOpenKeyExA(HKEY_CLASSES_ROOT,
        "CLSID\\{ADB880A6-D8FF-11CF-9377-00AA003B7A11}\\InprocServer32",
        0,
        KEY_READ,
        &hKey
    )) {
        return FALSE;
    }

    DWORD cbData = 260;
    BOOL result = FALSE;

    if (RegQueryValueExA(hKey, "", NULL, NULL, (LPBYTE)outputLibraryName, &cbData) == 0) {
        result = TRUE;
    }

    RegCloseKey(hKey);
    return TRUE;
}

void DisplayHelpWindow(HWND hDesktopWnd, LPCSTR lpChmFilename, UINT uCommand, DWORD_PTR dwData) {
    if (HtmlHelpModuleHandle == NULL && ErrorLoadingHelpFunc == FALSE) {
        CHAR libFileName[260];

        if (FindHtmlHelpDLL(libFileName)) {
            HtmlHelpModuleHandle = LoadLibraryA(libFileName);
        }

        if (HtmlHelpModuleHandle == NULL) {
            HtmlHelpModuleHandle = LoadLibraryA("hhctrl.ocx");
        }

        if (HtmlHelpModuleHandle == NULL) {
            ErrorLoadingHelpFunc = TRUE;
            return;
        }

        if (HtmlHelpWPtr == NULL) {
            HtmlHelpWPtr = (HTMLHELPWPROC)GetProcAddress(HtmlHelpModuleHandle, (LPCSTR)HtmlHelpW_ExportOrdinal);

            if (HtmlHelpWPtr == NULL) {
                ErrorLoadingHelpFunc = TRUE;
                return;
            }
        }

        // WIERD!
        // Using HtmlHelpW with ascii instead of unicode filename???
        HtmlHelpWPtr(hDesktopWnd, (LPCWSTR)lpChmFilename, uCommand, dwData);
    }
}

void ShowHelpHtml(DWORD arg0, UINT uCommand) {
    CHAR ChmFilename[250];

    if (arg0 == 4) {
        // WIERD: Missing NULL Terminator
        memcpy(ChmFilename, "NTHelp.chm", 10);
    }
    else {
        DWORD dwLength = GetModuleFileNameA(hModule, ChmFilename, sizeof(ChmFilename));

        // Point to the last char (the last e of the exe)
        PSTR copyDest = &ChmFilename[dwLength - 1];
        PSTR lastCharPointer = copyDest;

        if ((lastCharPointer - ChmFilename) > 4  // the file is at least 5 chars
            && *(lastCharPointer - 3) == '.') { // there is a dot before the 'exe'
            copyDest = lastCharPointer - 3;
        }

        // WIERD: Buffer overflow copying ".chm"
        memcpy(copyDest, ".chm", 4);
    }

    DisplayHelpWindow(GetDesktopWindow(), ChmFilename, uCommand, (DWORD_PTR)NULL);
}