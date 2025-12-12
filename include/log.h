/*
File: log.h
Developer: ColorProgrammy

Description:
Header file for log.cpp
*/

#pragma once
#include <fstream>
#include <ctime>
#include <string>
#include <windows.h>
#include <Shlobj.h>

class Log {
private:
    static int successCount;
    static int errorCount;
    static std::wstring logPath;
    
public:
    static void init(const std::string& folderName, const std::string& logFileName);
    static void write(const std::string& message, int status = 0); // 0 - INFO, 1 - SUCCESS, 2 - ERROR
    void init(const std::wstring &folderName, const std::wstring &logFileName);
    static void writeStats();
};

BOOL WINAPI ConsoleHandler(DWORD signal);