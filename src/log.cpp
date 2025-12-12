/*
File: log.cpp
Developer: ColorProgrammy

Description:
Creating logs
*/

#define _CRT_SECURE_NO_WARNINGS

#include "../include/log.h"
#include <time.h>
#include <fstream>
#include <iostream>

std::wstring Log::logPath;
int Log::successCount = 0;
int Log::errorCount = 0;



void Log::init(const std::string& folderName, const std::string& logFileName) {
    PWSTR documentsPath = NULL;
    SHGetKnownFolderPath(FOLDERID_Documents, 0, NULL, &documentsPath);

    std::wstring fullPath = std::wstring(documentsPath) + L"\\" + 
                           std::wstring(folderName.begin(), folderName.end());
    
    CreateDirectoryW(fullPath.c_str(), NULL);

    logPath = fullPath + L"\\" + std::wstring(logFileName.begin(), logFileName.end());

    CoTaskMemFree(documentsPath);

    std::ofstream logFile(logPath.c_str(), std::ios::out | std::ios::trunc);
    if (!logFile.is_open()) {
        std::wcerr << L"Error opening log file: " << logPath << std::endl;
        return;
    }
    logFile.close();

    successCount = 0;
    errorCount = 0;
}

void Log::write(const std::string& message, int status) {
    if (status == 1) {
        successCount++;
    } else if (status == 2) {
        errorCount++;
    }

    time_t now = time(NULL);
    tm* timeinfo = localtime(&now);
    char buffer[80];
    strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", timeinfo);

    std::string statusText;
    switch (status) {
        case 0: statusText = "[i]"; break;
        case 1: statusText = "[+]"; break;
        case 2: statusText = "[-]"; break;
    }

    // Open file with wide string path directly
    std::wofstream logFile(logPath.c_str(), std::ios::app);
    if (logFile.is_open()) {
        // Convert message to wstring for proper Unicode handling
        std::wstring wmessage(message.begin(), message.end());
        std::wstring wstatusText(statusText.begin(), statusText.end());
        std::wstring wbuffer(buffer, buffer + strlen(buffer));
        
        logFile << L"[" << wbuffer << L"] " << wstatusText << L": " << wmessage << std::endl;
        logFile.close();
    }
}


void Log::writeStats() {
    std::wofstream logFile(logPath.c_str(), std::ios::app);
    if (logFile) {
        logFile << L"\nStatistics:" << std::endl;
		logFile << L"Total operations [+/-]: " << (successCount + errorCount) << std::endl;
        logFile << L"Successful operations [+]: " << successCount << std::endl;
        logFile << L"Failed operations [-]: " << errorCount << std::endl;
        logFile.close();
    }
}

BOOL WINAPI ConsoleHandler(DWORD signal) {
    Log::write("Application closed.", 0);
    Log::write("---", 0);
    Log::writeStats();
    return TRUE;
}