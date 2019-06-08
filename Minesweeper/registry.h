#pragma once
#include <Windows.h>

extern HKEY hRegistryKey;
extern LPCWSTR RegistryValuesNames[];

typedef enum _RegistryValue {
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
} RegistryValue;

VOID GetStringFromRegistry(RegistryValue id, LPWSTR lpData);

int GetIntegerFromRegistry(RegistryValue regValue, int defaultValue, int minValue, int maxValue);