#pragma once
#include <Windows.h>

#define SOUND_ON 3
#define SOUNDTYPE_TICK 1
#define SOUNDTYPE_WIN 2
#define SOUNDTYPE_LOSE 3

// Sound Functions
DWORD StopAllSound();
void FreeSound();
void PlayGameSound(DWORD soundType);