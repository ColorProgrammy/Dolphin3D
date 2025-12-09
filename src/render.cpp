#include "../include/globals.h"
#include "../include/Vector2.h"
#include "../include/Vector3.h"
#include "../include/functions.h"
#include "../include/setup.h"
#include "../include/objects.hpp"
#include "../include/color.h"
#include "../include/render.h"
#include "../include/log.h"

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
    const size_t bufferSize = static_cast<size_t>(width) * height;
    
    if (currentBuffer) {
        freeBuffers();
    }

    try {
        currentBuffer = new CHAR_INFO[bufferSize];
        displayBuffer = new CHAR_INFO[bufferSize];
        
        // Initialize both buffers properly
        for (size_t i = 0; i < bufferSize; i++) {
            currentBuffer[i].Char.AsciiChar = ' ';
            currentBuffer[i].Attributes = 15;
            displayBuffer[i].Char.AsciiChar = ' ';
            displayBuffer[i].Attributes = 15;
        }
    }
    catch (const std::bad_alloc&) {
        Log::write("Memory allocation failed - buffer size too large", 2);
        freeBuffers();
        _getch();
        exit(1);
    }
}

void render(int width, int height, int fps) {
    if (!currentBuffer || !displayBuffer) return;

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole == INVALID_HANDLE_VALUE) return;

    COORD bufferSize = { (SHORT)width, (SHORT)height };
    COORD coord = { 0, 0 };
    SMALL_RECT rect = { 0, 0, (SHORT)(width - 1), (SHORT)(height - 1) };

    WriteConsoleOutput(hConsole, displayBuffer, bufferSize, coord, &rect);

	if (hConsole == INVALID_HANDLE_VALUE) {
		_getch();
        exit(1);
    }

    CONSOLE_CURSOR_INFO cursorInfo;
    if (!GetConsoleCursorInfo(hConsole, &cursorInfo)) {
		_getch();
        exit(1);
    }

    cursorInfo.bVisible = FALSE;
    if (!SetConsoleCursorInfo(hConsole, &cursorInfo)) {
		_getch();
        exit(1);
    }

    if (fps > 0) {
        // Calculate the sleep duration based on the desired frame rate
        int sleepDuration = 1000 / fps;
        Sleep(sleepDuration);
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

void setColors(int i, int j, int width, size_t gradientSize, const char* gradient, bool hit, Color currentcolor, float brightness) {
    static bool firstCall = true;
    if (firstCall) {
        Log::write("\"setColors\" in progress...", 0);
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

        if (r > 128) color |= FOREGROUND_RED;
        if (g > 128) color |= FOREGROUND_GREEN;
        if (b > 128) color |= FOREGROUND_BLUE;
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
        Log::write("Color setting initialized successfully", 1);
        firstSuccess = false;
    }
}

void createPointLight(std::vector<Light>& lights, vec3 position, float intensity, float radius) {
    lights.push_back(Light(position, intensity, radius));
}

void createSpotlight(std::vector<Light>& lights, vec3 position, vec3 direction, float intensity, float radius, float angle) {
    lights.push_back(Light(position, direction, intensity, radius, angle));
}

void createDirectionalLight(std::vector<Light>& lights, vec3 position, vec3 direction, float intensity, float width, float range) {
    // Используем конструктор прожектора, но меняем тип на DIRECTIONAL
    lights.push_back(Light(position, direction, intensity, range, width));
    lights.back().type = LIGHT_DIRECTIONAL; // Меняем тип после создания
}

void setObjects(std::vector<Object*>& objects, vec3& ro, vec3& rd, bool& hit, 
               Color& currentcolor, float& brightness, vec3& normal, 
               std::vector<Light>& lights, float shadowBrightness, 
               float shadowDistance) {
    static bool firstCall = true;
    if (firstCall) {
        Log::write("\"setObjects\" in progress...", 0);
        firstCall = false;
    }

    float minDist = FLT_MAX;
    hit = false;
    currentcolor = Color::Black();
    Object* closestObj = NULL;
    float currentAlbedo = 1.0f;

    for (size_t k = 0; k < objects.size(); ++k) {
        Object* obj = objects[k];
        float currentDist = FLT_MAX;
        vec3 n;
        if (obj->set(ro, rd, currentDist, n)) {
            if (currentDist < minDist && currentDist > 0.001f) {
                minDist = currentDist;
                normal = n;
                closestObj = obj;
                currentAlbedo = obj->getAlbedo();
                currentcolor = obj->getColor();
                hit = true;
            }
        }
    }

    if (hit) {
        float bias = max(0.001f, minDist * 0.001f);
        vec3 hitPoint = ro + rd * (minDist - bias);
        brightness = 0.1f; // Базовое окружающее освещение

        for (size_t l = 0; l < lights.size(); ++l) {
            Light& light = lights[l];
            
            if (light.type == LIGHT_DIRECTIONAL) {
    // Для направленного света - используем физику точечного света
    vec3 toLight = light.position - hitPoint;
    float lightDist = length(toLight);
    vec3 lightDir = norm(toLight);
    
    // Проверяем, находится ли точка в пределах конуса направленного света
    vec3 lightMainDir = norm(light.direction);
    float cosAngle = dot(lightDir, lightMainDir);
    float angleThreshold = cos(light.angle * 0.5f);
    
    if (cosAngle < angleThreshold) continue;
    
    // Затухание как у точечного света
    float t = lightDist / light.radius;
    float fade = smoothstep(1.0f, 0.8f, t);
    float attenuation = (1.0f / (1.0f + 0.1f * pow(lightDist, 2.0f))) * fade * light.intensity;
    
    // **ИСПРАВЛЕНИЕ ДЛЯ ТЕНЕЙ** - используем ТОЧНО ту же логику, что и для точечного света
    bool inShadow = false;
    vec3 shadowRayOrigin = hitPoint + normal * bias;
    
    for (size_t k = 0; k < objects.size(); ++k) {
        Object* obj = objects[k];
        if(obj == closestObj) continue;

        vec3 shadowNormal;
        float shadowDist = FLT_MAX;
        
        // **ВАЖНО**: используем lightDir (направление к источнику), а не lightMainDir
        if(obj->set(shadowRayOrigin, lightDir, shadowDist, shadowNormal)) {
            if(shadowDist > 0.001f && shadowDist < lightDist) {
                inShadow = true;
                break;
            }
        }
    }

    // Освещенность - используем основное направление для равномерности
    float lightFactor = max(dot(normal, lightMainDir), 0.0f) * currentAlbedo;
    
    if(inShadow) {
        brightness += lightFactor * shadowBrightness * attenuation;
    } else {
        brightness += lightFactor * attenuation;
    }




			} else {
                // Для точечного и прожекторного света - существующая логика
                vec3 toLight = light.position - hitPoint;
                float lightDist = length(toLight);
                vec3 lightDir = norm(toLight);
                
                if (light.type == LIGHT_POINT) {
                    float t = lightDist / light.radius;
                    float fade = smoothstep(1.0f, 0.8f, t);
                    float attenuation = (1.0f / (1.0f + pow(lightDist, 2.0f))) * fade * light.intensity;
                    
                    bool inShadow = false;
                    for (size_t k = 0; k < objects.size(); ++k) {
                        Object* obj = objects[k];
                        if(obj == closestObj) continue;

                        vec3 shadowNormal;
                        float shadowDist = FLT_MAX;
                        if(obj->set(hitPoint, lightDir, shadowDist, shadowNormal)) {
                            if(shadowDist > 0.001f && shadowDist < lightDist) {
                                inShadow = true;
                                break;
                            }
                        }
                    }

                    float lightFactor = max(dot(normal, lightDir), 0.0f) * currentAlbedo;
                    if(inShadow) {
                        brightness += lightFactor * shadowBrightness * attenuation;
                    } else {
                        brightness += lightFactor * attenuation;
                    }
                }
                // Для прожектора - аналогичная логика, но с угловой проверкой
            }
        }

        brightness = min(brightness, 1.0f);
        brightness = sqrtf(brightness); // Гамма-коррекция
        ro = hitPoint;
    }

    static bool firstSuccess = true;
    if (firstSuccess) {
        Log::write("Object setting initialized successfully", 1);
        firstSuccess = false;
    }
}

vec2 createUV(int i, int j, int width, int height) {
    float u = (i + 0.5f) / width * 2.0f - 1.0f;
    float v = (j + 0.5f) / height * 2.0f - 1.0f;
    u *= (float(width) / height) * 0.5f;
    return vec2(u, v);
}

void swapBuffers(CHAR_INFO* currentBuffer, CHAR_INFO* displayBuffer, int width, int height) {
    static bool firstCall = true;
    if (firstCall) {
        Log::write("Swapping buffers...", 0);
        firstCall = false;
    }

    int bufferSize = width * height;
    for (int i = 0; i < bufferSize; ++i) {
        memcpy(displayBuffer, currentBuffer, sizeof(CHAR_INFO) * width * height);
    }

    static bool firstSuccess = true;
    if (firstSuccess) {
        Log::write("Buffer swapping initialized successfully", 1);
        firstSuccess = false;
    }
}

