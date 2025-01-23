#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <windows.h>

struct Config {
    std::string title;
    std::string iconPath;
    int width;
    int height;
};

inline Config readConfig(const std::string& filename) {
    Config cfg;
    std::ifstream file(filename.c_str()); // Используем c_str() для преобразования std::string в const char*
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open config file '" << filename << "'" << std::endl;
		char currentWorkingDirectory[MAX_PATH];
		GetCurrentDirectory(MAX_PATH, currentWorkingDirectory);
		std::cout << "Current Working Directory: " << currentWorkingDirectory << std::endl;
		std::cout << "Press any key to quit" << std::endl;

		_getch();
        exit(1);
    }

    std::string line;
    std::string section;

    while (std::getline(file, line)) {
        line.erase(0, line.find_first_not_of(" \t"));
        if (line.empty() || line[0] == ';') continue;

        if (line[0] == '[') {
            section = line.substr(1, line.find(']') - 1);
        } else {
            size_t delimiterPos = line.find('=');
            std::string key = line.substr(0, delimiterPos);
            std::string value = line.substr(delimiterPos + 1);

            key.erase(0, key.find_first_not_of(" \t"));
            key.erase(key.find_last_not_of(" \t") + 1);
            value.erase(0, value.find_first_not_of(" \t"));
            value.erase(value.find_last_not_of(" \t") + 1);

            if (section == "Window") {
                if (key == "Title") {
                    cfg.title = value;
                } else if (key == "IconPath") {
                    cfg.iconPath = value;
                } else if (key == "Width") {
                    std::istringstream(value) >> cfg.width; // Используем std::istringstream для преобразования строки в int
                } else if (key == "Height") {
                    std::istringstream(value) >> cfg.height; // Используем std::istringstream для преобразования строки в int
                }
            }
        }
    }

    return cfg;
}

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
