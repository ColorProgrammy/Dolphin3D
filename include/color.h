#pragma once
#include <windows.h>

class Color {
public:
    Color() : r(0), g(0), b(0) {}
    Color(int r, int g, int b) : r(r), g(g), b(b) {}
    Color(const Color& other) : r(other.r), g(other.g), b(other.b) {}

    Color operator * (float f) const {
        return Color((int)(r * f), (int)(g * f), (int)(b * f));
    }

    static Color Red() { return Color(255, 0, 0); }
    static Color Green() { return Color(0, 255, 0); }
    static Color Blue() { return Color(0, 0, 255); }
    static Color White() { return Color(255, 255, 255); }
    static Color Black() { return Color(0, 0, 0); }
    static Color Yellow() { return Color(255,255,0); }
    static Color Cyan() { return Color(0,255,255); }
    static Color Magenta() { return Color(255,0,255); }

    DWORD toDWORD() const {
        return (b << 16) | (g << 8) | r;
    }

    void setConsoleColor(HANDLE hConsole) const {
        SetConsoleTextAttribute(hConsole, (WORD)toDWORD());
    }
private:
    int r;
    int g;
    int b;
};
