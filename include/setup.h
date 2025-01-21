#include <Windows.h>
#include "globals.h"
#include <string>


inline void setIcon(const char* iconPath) {
    char currentWorkingDirectory[MAX_PATH];
    GetCurrentDirectory(MAX_PATH, currentWorkingDirectory);

    char fullIconPath[MAX_PATH];
    strcpy_s(fullIconPath, currentWorkingDirectory);
    strcat_s(fullIconPath, "\\");
    strcat_s(fullIconPath, iconPath);

    HICON hIcon = (HICON)LoadImage(NULL, fullIconPath, IMAGE_ICON, 0, 0, LR_LOADFROMFILE | LR_DEFAULTSIZE);
    SendMessage(GetConsoleWindow(), WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
    SendMessage(GetConsoleWindow(), WM_SETICON, ICON_BIG, (LPARAM)hIcon);
}

inline bool setWindow(int width, int height, const std::string& title) {
    SetConsoleTitleA(title.c_str());	
	char modeCommand[50];	

    sprintf_s(modeCommand, "mode con cols=%d lines=%d", width, height);
    int result = system(modeCommand);
    return result == 0;

}