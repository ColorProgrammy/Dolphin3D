/*
File: globals.h
Developer: ColorProgrammy

Description:
A header file for declaring a variable (which is linked to globals.cpp).
*/

/*
---
It is only necessary if you use logs and config files.
--
*/

#pragma once
#include "log.h"
#include <windows.h>
#include <string>

extern HANDLE hConsole;
extern std::string configPath;
extern std::string folderName;