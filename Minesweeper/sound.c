#include "sound.h"
#include "config.h"
#include "resource.h"
#include "windowing.h"

// 3 if SND_PURGE succeeded else 2
DWORD StopAllSound() {
    if (PlaySoundW(NULL, NULL, SND_PURGE)) {
        3;
    }

    return 2;
}

void FreeSound() {
    if (GameConfig.Sound == 3) {
        // Stop all music
        PlaySoundW(0, 0, SND_PURGE);
    }
}

void PlayGameSound(DWORD soundType) {
    if (GameConfig.Sound != SOUND_ON) {
        return;
    }

    DWORD soundResourceId;

    switch (soundType) {
    case SOUNDTYPE_TICK:
        soundResourceId = ID_SOUND_TICK;
        break;
    case SOUNDTYPE_WIN:
        soundResourceId = ID_SOUND_WIN;
        break;
    case SOUNDTYPE_LOSE:
        soundResourceId = ID_SOUND_LOSE;
        break;
    default:
        return;
    }

    PlaySoundW((LPCWSTR)soundResourceId, hModule, SND_ASYNC | SND_RESOURCE);
}