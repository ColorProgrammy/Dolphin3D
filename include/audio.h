/*
File: audio.h
Developer: ColorProgrammy

Description:
Library for playing audio
*/

#include <windows.h>
#pragma comment(lib, "winmm.lib")

void playSoundAsync(const char* soundFile) {
	char currentWorkingDirectory[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, currentWorkingDirectory);

    char fullSoundPath[MAX_PATH];
    strcpy_s(fullSoundPath, currentWorkingDirectory);
    strcat_s(fullSoundPath, "\\");
    strcat_s(fullSoundPath, soundFile);

    PlaySound(TEXT(fullSoundPath), NULL, SND_ASYNC | SND_FILENAME);
}

void playSoundSync(const char* soundFile) {
	char currentWorkingDirectory[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, currentWorkingDirectory);

    char fullSoundPath[MAX_PATH];
    strcpy_s(fullSoundPath, currentWorkingDirectory);
    strcat_s(fullSoundPath, "\\");
    strcat_s(fullSoundPath, soundFile);

    PlaySound(TEXT(fullSoundPath), NULL, SND_SYNC | SND_FILENAME);
}
