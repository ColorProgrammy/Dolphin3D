#include "../include/Dolphin3D.h"
#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>
#include <windows.h>
#include <conio.h>
#include <float.h>

CHAR_INFO* currentBuffer = NULL;
CHAR_INFO* displayBuffer = NULL;

void setBuffer(int width, int height) {
    static bool firstCall = true;
    if (firstCall) {
        std::cout << "Setting buffers..." << std::endl;
        Log::write("Setting buffers...", 0);
        firstCall = false;
    }

    if (currentBuffer) {
        freeBuffers();
    }

    const size_t bufferSize = static_cast<size_t>(width) * height;

    // Логирование размеров буферов
    std::ostringstream oss;
    oss << "Buffer size: " << bufferSize;
    Log::write(oss.str(), 0);

    try {
        currentBuffer = new CHAR_INFO[bufferSize];
        displayBuffer = new CHAR_INFO[bufferSize];

        ZeroMemory(currentBuffer, bufferSize * sizeof(CHAR_INFO));
        ZeroMemory(displayBuffer, bufferSize * sizeof(CHAR_INFO));
    }
    catch (const std::bad_alloc&) {
        Log::write("Memory allocation failed - buffer size too large", 2);
        freeBuffers();
        _getch();
        exit(1);
    }

    static bool firstSuccess = true;
    if (firstSuccess) {
        Log::write("Buffers allocated successfully", 1);
        firstSuccess = false;
    }
}
void render(int width, int height) {
    if (!currentBuffer || !displayBuffer) return;
    static bool firstCall = true;
    if (firstCall) {
        Log::write("Rendering...", 0);
        firstCall = false;
    }

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole == INVALID_HANDLE_VALUE) {
        Log::write("Invalid handle value", 2);
        return;
    }

    COORD coord = { 0, 0 };
    COORD bufferSize = { (SHORT)width, (SHORT)height };
    SMALL_RECT rect = { 0, 0, (SHORT)width - 1, (SHORT)height - 1 };

    CONSOLE_CURSOR_INFO cursorInfo;
    if (!GetConsoleCursorInfo(hConsole, &cursorInfo)) {
        Log::write("Failed to get cursor information", 2);
        _getch();
        exit(1);
    }

    cursorInfo.bVisible = FALSE;
    if (!SetConsoleCursorInfo(hConsole, &cursorInfo)) {
        Log::write("Failed to set cursor information", 2);
        _getch();
        exit(1);
    }

    WriteConsoleOutput(hConsole, displayBuffer, bufferSize, coord, &rect);
    SetConsoleTextAttribute(hConsole, 15);

    static bool firstSuccess = true;
    if (firstSuccess) {
        Log::write("Render system initialized successfully", 1);
        firstSuccess = false;
    }
}

bool initRender(int width, int height) {
    static bool firstCall = true;
    if (firstCall) {
        std::cout << "Initialization in progress..." << std::endl;
        Log::write("Initialization in progress...", 0);
        
        firstCall = false;
    }

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole == INVALID_HANDLE_VALUE) {
        std::cerr << "Error getting console handle!" << std::endl;
        Log::write("Error getting console handle!", 2);
        _getch();
        return false;
    }

    HWND consoleWindow = GetConsoleWindow();
    MoveWindow(consoleWindow, 0, 0, width * 8, height * 16, TRUE);
    LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
    style &= ~(WS_SIZEBOX | WS_MAXIMIZEBOX);
    SetWindowLong(consoleWindow, GWL_STYLE, style);
    SetWindowPos(consoleWindow, NULL, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOOWNERZORDER | SWP_FRAMECHANGED);

    static bool firstSuccess = true;
    if (firstSuccess) {
        Log::write("Render initialized successfully", 1);
        firstSuccess = false;
    }

    return true;
}

void freeBuffers() {
    static bool firstCall = true;
    if (firstCall) {
        Log::write("Freeing up buffers...", 0);
        firstCall = false;
    }
    delete[] currentBuffer;
    currentBuffer = NULL;
    delete[] displayBuffer;
    displayBuffer = NULL;

    static bool firstSuccess = true;
    if (firstSuccess) {
        Log::write("Buffers freed successfully", 1);
        firstSuccess = false;
    }
}

void freeObjects(std::vector<Object*>& objects) {
    static bool firstCall = true;
    if (firstCall) {
        Log::write("Freeing up objects...", 0);
        firstCall = false;
    }

    for (size_t i = 0; i < objects.size(); ++i) {
        delete objects[i];
    }
    objects.clear();

    static bool firstSuccess = true;
    if (firstSuccess) {
        Log::write("Objects freed successfully", 1);
        firstSuccess = false;
    }
}

void renderColor(int i, int j, int width, size_t gradientSize, const char* gradient, bool hit, Color currentcolor, float brightness) {
    static bool firstCall = true;
    if (firstCall) {
        Log::write("\"renderColor\" in progress...", 0);
        firstCall = false;
    }

    size_t colorIndex = static_cast<size_t>(brightness * 10.0f);
    colorIndex = min(max(colorIndex, static_cast<size_t>(0)), gradientSize);
    char pixel = gradient[colorIndex];
    currentBuffer[i + j * width].Char.AsciiChar = pixel;

    if (hit) {
        int color = 0;
        int r = currentcolor.getR();
        int g = currentcolor.getG();
        int b = currentcolor.getB();
        if (r > 0) color |= FOREGROUND_RED;
        if (g > 0) color |= FOREGROUND_GREEN;
        if (b > 0) color |= FOREGROUND_BLUE;
        if (r > 128 && g > 128) color |= FOREGROUND_RED | FOREGROUND_GREEN;
        if (r > 128 && b > 128) color |= FOREGROUND_RED | FOREGROUND_BLUE;
        if (g > 128 && b > 128) color |= FOREGROUND_GREEN | FOREGROUND_BLUE;
        if (r > 128 && g > 128 && b > 128) color |= FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
        currentBuffer[i + j * width].Attributes = color ? color : 7;
    } else {
        currentBuffer[i + j * width].Attributes = 15;
    }

    static bool firstSuccess = true;
    if (firstSuccess) {
        Log::write("Color rendering initialized successfully", 1);
        firstSuccess = false;
    }
}

void renderObjects(std::vector<Object*>& objects, vec3& ro, vec3& rd, bool& hit, Color& currentcolor, float& brightness, vec3& normal, vec3& light) {
    static bool firstCall = true;
    if (firstCall) {
        Log::write("\"renderObjects\" in progress...", 0);
        firstCall = false;
    }

    float lightRadius = 1.0f;
    float minDist = FLT_MAX;
    float currentAlbedo = 1.0f;
    float currentDist = FLT_MAX;
    hit = false;
    currentcolor = Color::Black();

    for (size_t k = 0; k < objects.size(); ++k) {
        Object* obj = objects[k];
        if (obj->set(ro, rd, currentDist, normal)) {
            if (currentDist < minDist) {
                minDist = currentDist;
                currentAlbedo = obj->getAlbedo();
                currentcolor = obj->getColor();
                hit = true;
            }
        }
    }

    if (currentDist < 99999.0f && hit) {
        vec3 shadowRayOrigin = ro + rd * (currentDist - 0.01f);
        vec3 lightDirection = norm(light - shadowRayOrigin);
        float lightDistance = length(light - shadowRayOrigin);
        bool inShadow = false;
        const float maxShadowDistance = 100.0f;

        for (size_t k = 0; k < objects.size(); ++k) {
            Object* obj = objects[k];
            vec3 shadowNormal;
            float shadowDist = FLT_MAX;
            if (obj->set(shadowRayOrigin, lightDirection, shadowDist, shadowNormal)) {
                if (shadowDist < lightDistance && shadowDist < lightRadius && shadowDist < maxShadowDistance) {
                    inShadow = true;
                    break;
                }
            }
        }

        if (inShadow) {
            brightness *= 0.7f * (dot(normal, lightDirection) * 0.5f + 0.5f) * currentAlbedo;
        } else {
            brightness *= (dot(normal, lightDirection) * 0.5f + 0.5f) * currentAlbedo;
        }

        ro = ro + rd * (currentDist - 0.01f);
        brightness = max(brightness, 0.0f);
    }

    static bool firstSuccess = true;
    if (firstSuccess) {
        Log::write("Object rendering initialized successfully", 1);
        firstSuccess = false;
    }
}

vec2 createUV(int i, int j, int width, int height) {
    static bool firstCall = true;
    if (firstCall) {
        Log::write("Creating UV...", 0);
        firstCall = false;
    }

    float aspect = (float)width / height;
    float pixelAspect = 8.0f / 16.0f;
    vec2 uv = (vec2(static_cast<float>(i), static_cast<float>(j)) / vec2(static_cast<float>(width), static_cast<float>(height))) * 2 - 1;
    uv.x *= aspect * pixelAspect;

    static bool firstSuccess = true;
    if (firstSuccess) {
        Log::write("UV system initialized successfully", 1);
        firstSuccess = false;
    }
    return uv;
}

void swapBuffers(CHAR_INFO* currentBuffer, CHAR_INFO* displayBuffer, int width, int height) {
    static bool firstCall = true;
    if (firstCall) {
        Log::write("Swapping buffers...", 0);
        firstCall = false;
    }

    int bufferSize = width * height;
    for (int i = 0; i < bufferSize; ++i) {
        std::swap(currentBuffer[i], displayBuffer[i]);
    }

    static bool firstSuccess = true;
    if (firstSuccess) {
        Log::write("Buffer swapping initialized successfully", 1);
        firstSuccess = false;
    }
}
