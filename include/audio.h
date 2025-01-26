/*
File: audio.h
Developer: ColorProgrammy

Description:
Library for playing audio
*/

#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#pragma comment(lib, "winmm.lib")

inline void playSoundAsync(const char* soundFile) {
    char currentWorkingDirectory[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, currentWorkingDirectory);
    char fullSoundPath[MAX_PATH];
    strcpy_s(fullSoundPath, MAX_PATH, currentWorkingDirectory);
    strcat_s(fullSoundPath, MAX_PATH, "\\");
    strcat_s(fullSoundPath, MAX_PATH, soundFile);
    PlaySound(TEXT(fullSoundPath), NULL, SND_ASYNC | SND_FILENAME);
}

inline void playSoundSync(const char* soundFile) {
    char currentWorkingDirectory[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, currentWorkingDirectory);
    char fullSoundPath[MAX_PATH];
    strcpy_s(fullSoundPath, MAX_PATH, currentWorkingDirectory);
    strcat_s(fullSoundPath, MAX_PATH, "\\");
    strcat_s(fullSoundPath, MAX_PATH, soundFile);
    PlaySound(TEXT(fullSoundPath), NULL, SND_SYNC | SND_FILENAME);
}
