#include "include/render.h"
#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>
#include <windows.h>
#include <conio.h>
#include <float.h>
#include "include/Vector2.h"
#include "include/Vector3.h"
#include "include/functions.h"
#include "include/audio.h"
#include "include/setup.h"
#include "include/objects.h"
#include "include/color.h"


CHAR_INFO* currentBuffer = NULL;
CHAR_INFO* displayBuffer = NULL;

void setBuffer(int width, int height) {
    if (currentBuffer) {
      freeBuffers();
    }
    currentBuffer = new CHAR_INFO[width * height];
    displayBuffer = new CHAR_INFO[width * height];
    if (!currentBuffer || !displayBuffer) {
        std::cerr << "Memory allocation failed!" << std::endl;
        exit(1);
    }
}

void render(int width, int height){
  if (!currentBuffer || !displayBuffer) return;

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole == INVALID_HANDLE_VALUE) return;

    DWORD dwBytesWritten;
    COORD coord = { 0, 0 };
    COORD bufferSize = { (SHORT)width, (SHORT)height };
    SMALL_RECT rect = { 0, 0, (SHORT)width - 1, (SHORT)height - 1 };

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

	WriteConsoleOutput(hConsole, displayBuffer, bufferSize, coord, &rect);
	SetConsoleTextAttribute(hConsole, 15);
}


bool initRender(int width, int height) {
    // Initialize console window and buffer
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole == INVALID_HANDLE_VALUE) {
        std::cerr << "Error getting console handle!" << std::endl;
		_getch();
        return false;
    }

	std::vector<Object*> objects;


    // Allocate buffers
    //setBuffer(width, height);
    if (!currentBuffer || !displayBuffer) {

        freeBuffers(); //Clean up partial allocation
		_getch();
        return false;
    }
    return true; //Successfully init
}

void freeBuffers() {
    delete[] currentBuffer;
    currentBuffer = NULL;
    delete[] displayBuffer;
    displayBuffer = NULL;
}

void freeObjects(std::vector<Object*>& objects) {
    for (size_t i = 0; i < objects.size(); ++i) {
        delete objects[i];
    }
    objects.clear();
}
void renderColor(int i, int j, int width, size_t gradientSize, const char* gradient, bool hit, Color currentcolor, float brightness)
{
    int colorIndex = (int)(brightness * 10.0f);
    colorIndex = clamp(colorIndex, 0, gradientSize);
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
}

void renderObjects(std::vector<Object*>& objects, vec3& ro, vec3& rd, bool& hit, Color& currentcolor, float& brightness, vec3& normal, vec3& light, float lightRadius) {
    float minDist = FLT_MAX;
    float currentAlbedo = 1.0f;
    float currentDist = FLT_MAX;

    hit = false;
    currentcolor = Color::Black();

    // Поиск ближайшего объекта
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
        // Начальная позиция для расчета теней
        vec3 shadowRayOrigin = ro + rd * (currentDist - 0.01f);
        vec3 lightDirection = norm(light - shadowRayOrigin);
        float lightDistance = length(light - shadowRayOrigin);
        bool inShadow = false;

        // Установка максимального расстояния для теней
        const float maxShadowDistance = 100.0f;  // Установите нужное расстояние

        // Проверяем на наличие объектов между источником света и объектом
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

        // Рассчитываем яркость
        if (inShadow) {
            brightness *= 0.7f * (dot(normal, lightDirection) * 0.5f + 0.5f) * currentAlbedo; // Уменьшаем яркость в тени
        } else {
            brightness *= (dot(normal, lightDirection) * 0.5f + 0.5f) * currentAlbedo; // Полная яркость
        }

		ro = ro + rd * (currentDist - 0.01f); // Сдвиг при пересечении
        brightness = max(brightness, 0.0f); 
    }
}