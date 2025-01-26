#define _CRT_SECURE_NO_WARNINGS

#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <windows.h>
#include <shlobj.h>
#include <conio.h>
#include "log.h"
#include <stdio.h>
#include <KnownFolders.h>



struct Config {
    std::string title;
    std::string iconPath;
    int width;
    int height;
	std::string logPath;

};

inline Config readConfig(const std::string& filename) {
    Config cfg;
    std::ifstream file(filename.c_str());
    if (!file.is_open()) {
        std::cerr << "Warning: Unable to open config file '" << filename << "'" << std::endl;
        return cfg;
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
                    std::istringstream(value) >> cfg.width;
                } else if (key == "Height") {
                    std::istringstream(value) >> cfg.height;
                }
				else if (key == "LogPath") {
					cfg.logPath = value;
				}
            }
        }
    }

    return cfg;
}

inline Config readConfigFromFullPath(const std::string& fullPath) {
    Config cfg;
    std::ifstream file(fullPath.c_str());
    if (!file.is_open()) {
        std::cerr << "Warning: Unable to open config file '" << fullPath << "'" << std::endl;
        return cfg;
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
                    std::istringstream(value) >> cfg.width;
                } else if (key == "Height") {
                    std::istringstream(value) >> cfg.height;
				} else if (key == "LogPath") {
					cfg.logPath = value;
				}
            }
        }
    }

    return cfg;
}


inline void copyConfigFile(const std::string& folderName, const std::string& configFileName) {
    char documentsPath[MAX_PATH];
    SHGetFolderPathA(NULL, CSIDL_PERSONAL, NULL, 0, documentsPath);
    std::string newFolderPath = std::string(documentsPath) + "\\" + folderName;

    CreateDirectory(newFolderPath.c_str(), NULL);
    
    // Force copy config file
    std::string copyConfigCommand = "copy /Y \"" + configFileName + "\" \"" + 
                                  newFolderPath + "\\" + configFileName + "\"";
    system(copyConfigCommand.c_str());

    // Force copy assets folder
    std::string copyAssetsCommand = "xcopy /E /I /Y ..\\assets \"" + newFolderPath + "\\assets\"";
    system(copyAssetsCommand.c_str());
}

inline void initConsoleHandler() {
    SetConsoleCtrlHandler(ConsoleHandler, TRUE);
}

inline void createLogFile(const std::string& folderName, const Config& cfg) {
    wchar_t documentsPath[MAX_PATH];
    SHGetFolderPathW(NULL, CSIDL_PERSONAL, NULL, 0, documentsPath);
    
    Log::init(folderName, "log.txt");
    
    std::wstring logFullPath = std::wstring(documentsPath) + L"\\" + 
                              std::wstring(folderName.begin(), folderName.end()) + L"\\" + 
                              std::wstring(cfg.logPath.begin(), cfg.logPath.end());
    
    std::wofstream logFile(logFullPath.c_str(), std::ios::out | std::ios::trunc);
    if (!logFile) {
        std::wcerr << L"Error: Unable to create log file '" << logFullPath << L"'" << std::endl;
        _getch();
        exit(1);
    }
    
    Log::write("Title: " + cfg.title);
    std::stringstream ss;
    ss << "Window size: " << cfg.width << " x " << cfg.height;
    Log::write(ss.str());
    Log::write("---");
    Log::write("Loading...");
    Log::write("---");
    Log::write("Application opened.");
	initConsoleHandler();
    
    std::wcout << L"Log file created successfully: " << logFullPath << std::endl;
    logFile.close();
}


inline void setIcon(const Config& cfg, const std::string& folderName) {
    char documentsPath[MAX_PATH];
    SHGetFolderPathA(NULL, CSIDL_PERSONAL, NULL, 0, documentsPath);
    std::string iconFullPath = std::string(documentsPath) + "\\" + folderName + "\\" + cfg.iconPath;
    
    HICON hIcon = (HICON)LoadImageA(NULL, iconFullPath.c_str(), IMAGE_ICON, 0, 0, LR_LOADFROMFILE | LR_DEFAULTSIZE);
    
    if (hIcon) {
        HWND hwnd = GetConsoleWindow();
        SendMessage(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
        SendMessage(hwnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
    } else {
        std::cerr << "Error: Unable to load icon from '" << iconFullPath << "'" << std::endl;
        _getch();
        exit(1);
    }
}

inline bool setWindow(int width, int height, const std::string& title) {
    SetConsoleTitleA(title.c_str());
    char modeCommand[50];
    sprintf_s(modeCommand, sizeof(modeCommand), "mode con cols=%d lines=%d", width, height);
    int result = system(modeCommand);
    return result == 0;
}


inline bool setConfig(const std::string& folderName, const std::string& configPath, Config& cfg) {
    // First try - relative path from executable
    std::string relativePath = "..\\" + configPath;
    cfg = readConfigFromFullPath(relativePath);
    
    // If first attempt successful
    if (!cfg.title.empty()) {
        std::cout << "Config loaded successfully from relative path!" << std::endl;
        std::cout << "Title: " << cfg.title << std::endl;
        copyConfigFile(folderName, relativePath);
		createLogFile(folderName, cfg);
        return true;
    }

    // Second try - direct path
    cfg = readConfigFromFullPath(configPath);
    
    // If second attempt successful
    if (!cfg.title.empty()) {
        std::cout << "Config loaded successfully!" << std::endl;
        std::cout << "Title: " << cfg.title << std::endl;
        copyConfigFile(folderName, configPath);
		createLogFile(folderName, cfg);
        return true;
    }

    // Both attempts failed
    std::cerr << "Error: Config file not found in any location" << std::endl;
    return false;
}
