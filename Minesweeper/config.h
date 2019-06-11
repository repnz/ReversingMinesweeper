#pragma once
#include <Windows.h>

typedef enum {
    Difficulty,
    Mines,
    Height,
    Width,
    Xpos,
    Ypos,
    Sound,
    Mark,
    Menu,
    Tick,
    Color,
    Time1,
    Name1,
    Time2,
    Name2,
    Time3,
    BestExpertName,
    AlreadyPlayed
} ConfigItem;

#define TIME_BEGINNER 0
#define TIME_INTERMIDIATE 1
#define TIME_EXPERT 2

typedef WCHAR NameString[32];


// Those variables here are in the same order of the strings array
// It's seems like they are represented as a struct
typedef struct {
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
    DWORD Times[3];
    NameString Names[3];
} Config;

extern Config GameConfig;

int GetIntegerFromRegistry(ConfigItem regValue, int defaultValue, int minValue, int maxValue);
VOID GetStringFromRegistry(ConfigItem id, LPWSTR lpData);
void InitializeConfigFromRegistry();
void SetIntegerInRegistry(ConfigItem regValue, DWORD value);
void SetStringInRegistry(ConfigItem regValue, LPCWSTR lpStringValue);
void SaveConfigToRegistry();

int GetIntegerFromInitFile(ConfigItem regValue, int nDefault, DWORD minValue, DWORD maxValue);
int GetStringFromInitFile(ConfigItem regValue, LPWSTR lpReturnedString);
void InitMetricsAndFirstGame();