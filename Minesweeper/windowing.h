#pragma once
#include <Windows.h>


// Variables
extern WCHAR ClassName[32];
extern BOOL Is3x3Click;
extern BOOL HasMouseCapture;
extern HMODULE hModule;
extern HWND hWnd;
extern int ScreenHeightInPixels;
extern int WindowWidthInPixels;
extern int yBottom;
extern int xRight;
extern int MenuBarHeightInPixels;
extern int WindowHeightInPixels;

// Enum
#define WINDOW_BORDER_MOVE_WINDOW 2
#define WINDOW_BORDER_REPAINT_WINDOW 4

#define DIFFICULTY_BEGINNER 0
#define DIFFICULTY_INTERMEDIATE 1
#define DIFFICULTY_EXPERT 2
#define DIFFICULTY_CUSTOM 3

#define TIMER_ID 1

// Functions
BOOL HandleLeftClick(DWORD dwLocation);
void InitializeCheckedMenuItems();
INT_PTR CALLBACK CustomFieldDialogProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK SaveWinnerNameDialogProc(HWND hDialog, UINT uMsg, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK WinnersDialogProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
void SaveWinnerNameDialogBox();
DWORD SimpleGetSystemMetrics(DWORD val);
void InitializeWindowBorder(DWORD flags);
void CustomFieldDialogBox();
void ShowWinnerNameAndTime(HWND hDlg, int nIDDlgItem, int secondsLeft, LPCWSTR lpName);
void WinnersDialogBox();
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
__inline BOOL MenuHandler(WORD menuItem);
__inline void KeyDownHandler(WPARAM wParam);
__inline LRESULT CaptureMouseInput(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
__inline LRESULT MouseMoveHandler(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);

void SetMenuItemState(DWORD uID, BOOL isChecked);
void InitializeMenu(DWORD menuFlags);

int GetDlgIntOfRange(HWND hDlg, int nIDDlgItem, int min, int max);
