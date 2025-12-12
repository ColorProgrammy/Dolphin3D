/*
File: globals.cpp
Developer: ColorProgrammy

Description:
A source file for declaring a variable
*/

#include "../include/globals.h"
#include <Shlobj.h>

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
std::string configPath = "config.ini";
std::string folderName = "PointLight";
