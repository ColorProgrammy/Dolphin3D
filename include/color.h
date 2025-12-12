/*
File: color.h
Developer: ColorProgrammy

Description:
The color library
*/

#ifndef COLOR_H
#define COLOR_H

#include <windows.h>

class Color {
private:
    int r, g, b;

public:
    Color() : r(0), g(0), b(0) {}
    Color(int red, int green, int blue) : r(red), g(green), b(blue) {}

    void setConsoleColor(HANDLE hConsole) {
        int color = 0;
        if (r > 128) color |= FOREGROUND_RED;
        if (g > 128) color |= FOREGROUND_GREEN;
        if (b > 128) color |= FOREGROUND_BLUE;
        if (r > 128 && g > 128) color |= FOREGROUND_RED | FOREGROUND_GREEN;
        if (r > 128 && b > 128) color |= FOREGROUND_RED | FOREGROUND_BLUE;
        if (g > 128 && b > 128) color |= FOREGROUND_GREEN | FOREGROUND_BLUE;
        if (r > 128 && g > 128 && b > 128) color |= FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;

        SetConsoleTextAttribute(hConsole, color ? color : 7);
    }

    void setConsoleBackgroundColor(HANDLE hConsole) {
        int color = 0;
        if (r > 128) color |= BACKGROUND_RED;
        if (g > 128) color |= BACKGROUND_GREEN;
        if (b > 128) color |= BACKGROUND_BLUE;
        if (r > 128 && g > 128) color |= BACKGROUND_RED | BACKGROUND_GREEN;
        if (r > 128 && b > 128) color |= BACKGROUND_RED | BACKGROUND_BLUE;
        if (g > 128 && b > 128) color |= BACKGROUND_GREEN | BACKGROUND_BLUE;
        if (r > 128 && g > 128 && b > 128) color |= BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;

        SetConsoleTextAttribute(hConsole, color ? color : 0);
    }

    int getR() const { return r; }
    int getG() const { return g; }
    int getB() const { return b; }


    static Color White() { return Color(255, 255, 255); }
    static Color Black() { return Color(0, 0, 0); }
    static Color Red() { return Color(255, 0, 0); }
    static Color Green() { return Color(0, 255, 0); }
    static Color Blue() { return Color(0, 0, 255); }
    static Color Grey() { return Color(128, 128, 128); }
    static Color Yellow() { return Color(255, 255, 0); }
    static Color Magenta() { return Color(255, 0, 255); }
    static Color Cyan() { return Color(0, 255, 255); }
};

#endif // COLOR_H