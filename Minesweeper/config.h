#pragma once
#include <Windows.h>

#define CONFIG_DIFFICULTY 0
#define CONFIG_MINES 1
#define CONFIG_HEIGHT 2
#define CONFIG_WIDTH 3
#define CONFIG_XPOS 4
#define CONFIG_YPOS 5
#define CONFIG_SOUND 6
#define CONFIG_MARK 7
#define CONFIG_MENU 8
#define CONFIG_TICK 9
#define CONFIG_COLOR 10
#define CONFIG_TIME1 11
#define CONFIG_NAME1 12
#define CONFIG_TIME2 13
#define CONFIG_NAME2 14
#define CONFIG_TIME3 15
#define CONFIG_NAME3 16
#define CONFIG_ALREADY_PLAYED 17

#define TIME_BEGINNER 0
#define TIME_INTERMIDIATE 1
#define TIME_EXPERT 2

#define NAME_BEGINNER 0
#define NAME_INTERMIDIATE 1
#define NAME_EXPERT 2

typedef WCHAR NameString[32];


// Those variables here are in the same order of the strings array
// It's seems like they are represented as a struct
typedef struct _Config {
    short Difficulty;
    int Mines;

    DWORD Height;
    DWORD Width;

    // In Pixels, Screen Coordinates
    int Xpos;
    int Ypos;

    // 0 -> there is no sound
    // 1 -> ?
    // 2 -> could not call SND_PURGE / called FreeSound
    // 3 -> Sound is playing
    int Sound;
    int Mark;
    int Tick;
    int Menu;
    BOOL Color;
    int Times[3];
    NameString Names[3];
} Config;

extern Config GameConfig;
extern BOOL NeedToSaveConfigToRegistry;
extern WCHAR SecondsLeftBuffer[];
extern WCHAR AnonymousStr[];

void InitializeConfigFromRegistry();
void SaveConfigToRegistry();
void InitMetricsAndFirstGame();