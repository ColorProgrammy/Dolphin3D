/*
File: setup.h
Developer: ColorProgrammy

Description:
Several functions for the framework setup
*/

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


#pragma warning(push)
#pragma warning(disable : 4996)

struct Config {
    std::string title;
    std::string iconPath;
    int width;
    int height;
	std::string logPath;
	bool enableLogging;
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
            }
			if (section == "Logging") {
				if (key == "EnableLogging") {
					cfg.enableLogging = (value == "true" || value == "1");
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
                }
            }
			if (section == "Logging") {
				if (key == "EnableLogging") {
					cfg.enableLogging = (value == "true" || value == "1");
			}
				else if (key == "LogPath") {
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

    std::string configSource = configFileName;
    std::string configDest = newFolderPath + "\\" + configFileName;
    
    std::ifstream srcConfig(configSource.c_str(), std::ios::binary);
    std::ofstream dstConfig(configDest.c_str(), std::ios::binary);
    dstConfig << srcConfig.rdbuf();

	std::string copyConfigCommand = "copy /Y \"" + configFileName + "\" \"" + 
                                  newFolderPath + "\\" + configFileName + "\"";
    system(copyConfigCommand.c_str());

    std::string assetsPath = "..\\assets";
    DWORD fileAttributes = GetFileAttributesA(assetsPath.c_str());

    if (fileAttributes != INVALID_FILE_ATTRIBUTES && (fileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
        std::string command = "xcopy /E /I /Y ..\\assets \"" + newFolderPath + "\\assets\"";
        system(command.c_str());
        std::cout << "Assets folder copied successfully." << std::endl;
    } else {
        std::cout << "Assets folder not found. Skipping copy." << std::endl;
    }
}

inline void createLogFile(const std::string& folderName, const Config& cfg) {
    if (!cfg.enableLogging) {
        return; // If logging is disabled, do nothing
    }

    char documentsPath[MAX_PATH];
    SHGetFolderPathA(NULL, CSIDL_PERSONAL, NULL, 0, documentsPath);
    
    // Forming the full path to the log file
    std::string fullPath = std::string(documentsPath) + "\\" + folderName + "\\" + cfg.logPath;

    std::string dirPath = std::string(documentsPath) + "\\" + folderName;
    size_t pos = cfg.logPath.find_last_of("\\/");
    if (pos != std::string::npos) {
        dirPath += "\\" + cfg.logPath.substr(0, pos);
        if (!CreateDirectoryA(dirPath.c_str(), NULL)) {
            DWORD err = GetLastError();
            if (err != ERROR_ALREADY_EXISTS) {
                std::cerr << "Error creating log directory: " << dirPath << std::endl;
                _getch();
                exit(1);
            }
        }
    }

    Log::init(folderName, cfg.logPath);

	std::stringstream ss;
	ss << "Window size: " << cfg.width << " x " << cfg.height;

    Log::write("Title: " + cfg.title);
    Log::write(ss.str());
    Log::write("---");
    Log::write("Loading...");
    Log::write("---");
    Log::write("Application opened.");

    SetConsoleCtrlHandler(ConsoleHandler, TRUE);

    std::cout << "Log file created successfully: " << fullPath << std::endl;
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
    _snprintf(modeCommand, sizeof(modeCommand), "mode con cols=%d lines=%d", width, height);
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

#pragma warning(pop)