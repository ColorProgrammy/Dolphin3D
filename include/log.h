#pragma once
#include <fstream>
#include <ctime>
#include <string>
#include <windows.h>
#include <Shlobj.h>

class Log {
private:
    static std::wstring logPath;
    
public:
    static void init(const std::string& folderName, const std::string& logFileName) {
        wchar_t documentsPath[MAX_PATH];
        SHGetFolderPathW(NULL, CSIDL_MYDOCUMENTS, NULL, 0, documentsPath);
        
        logPath = std::wstring(documentsPath) + L"\\" + 
                 std::wstring(folderName.begin(), folderName.end()) + L"\\" +
                 std::wstring(logFileName.begin(), logFileName.end());
    }

    static void write(const std::string& message) {
        time_t now = time(NULL);
        tm timeinfo;
        localtime_s(&timeinfo, &now);
        char buffer[80];
        strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", &timeinfo);

        std::ofstream logFile(logPath.c_str(), std::ios::app);
        if (logFile) {
            logFile << "[" << buffer << "] " << message << std::endl;
            logFile.close();
        }
    }
};