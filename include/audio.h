/*
File: audio.h
Developer: ColorProgrammy

Description:
Library for playing audio
*/

#ifndef AUDIO_H
#define AUDIO_H

#include <windows.h>
#pragma comment(lib, "winmm.lib")

inline void playSoundAsync(const char* soundFile) {
    char currentWorkingDirectory[MAX_PATH];
    GetCurrentDirectoryA(MAX_PATH, currentWorkingDirectory);
    char fullSoundPath[MAX_PATH];
    strcpy(fullSoundPath, currentWorkingDirectory);
    strcat(fullSoundPath, "\\");
    strcat(fullSoundPath, soundFile);
    PlaySoundA(fullSoundPath, NULL, SND_ASYNC | SND_FILENAME);
}

inline void playSoundSync(const char* soundFile) {
    char currentWorkingDirectory[MAX_PATH];
    GetCurrentDirectoryA(MAX_PATH, currentWorkingDirectory);
    char fullSoundPath[MAX_PATH];
    strcpy(fullSoundPath, currentWorkingDirectory);
    strcat(fullSoundPath, "\\");
    strcat(fullSoundPath, soundFile);
    PlaySoundA(fullSoundPath, NULL, SND_SYNC | SND_FILENAME);
}

#endif // AUDIO_H