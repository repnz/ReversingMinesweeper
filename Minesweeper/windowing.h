#pragma once
#include <Windows.h>


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
