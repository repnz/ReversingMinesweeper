#pragma once
#include <Windows.h>

extern HKEY hRegistryKey;
extern LPCWSTR RegistryValuesNames[];

enum RegistryValue {
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
    BestBeginnerTime,
    BestBeginnerName,
    BestIntermidiateTime,
    BestIntermidiateName,
    BestExpertTime,
    BestExpertName,
    AlreadyPlayed
};

VOID GetStringFromRegistry(RegistryValue id, LPWSTR lpData);

int GetIntegerFromRegistry(RegistryValue regValue, int defaultValue, int minValue, int maxValue);