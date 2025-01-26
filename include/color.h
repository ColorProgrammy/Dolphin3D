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
        int r_index = (r * 5) / 255;
        int g_index = (g * 5) / 255;
        int b_index = (b * 5) / 255;

        int color = 0;
        if (r_index > 0) color |= FOREGROUND_RED;
        if (g_index > 0) color |= FOREGROUND_GREEN;
        if (b_index > 0) color |= FOREGROUND_BLUE;

        SetConsoleTextAttribute(hConsole, color ? color : 7); 
    }

    void setConsoleBackgroundColor(HANDLE hConsole) {
        int r_index = (r * 5) / 255;
        int g_index = (g * 5) / 255;
        int b_index = (b * 5) / 255;

        int color = 0;
        if (r_index > 0) color |= BACKGROUND_RED;
        if (g_index > 0) color |= BACKGROUND_GREEN;
        if (b_index > 0) color |= BACKGROUND_BLUE;

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
