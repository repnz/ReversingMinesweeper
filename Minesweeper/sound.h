#pragma once
#include <Windows.h>

// Sound Functions
DWORD StopAllSound();
void FreeSound();
void PlayGameSound(DWORD soundType);