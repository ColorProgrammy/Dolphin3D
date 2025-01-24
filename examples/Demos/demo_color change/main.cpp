#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>
#include <windows.h>
#include <conio.h>
#include "../include/Dolphin3D.h"

// Continuous color change function
DWORD WINAPI changeBoxColor(LPVOID lpParam) {
    Box* box = static_cast<Box*>(lpParam);
    while (true) {
        box->setColor(Color::Green());
        Sleep(1000);
        box->setColor(Color::Yellow());
        Sleep(1000);
        box->setColor(Color::Cyan());
        Sleep(1000);
        box->setColor(Color::White());
        Sleep(1000);
        box->setColor(Color::Blue());
        Sleep(1000);
    }
    return 0;
}

int main() {
    bool hit;
    Color currentcolor;
    vec3 normal;

    Config cfg = readConfig("config.ini");

    int width = cfg.width;
    int height = cfg.height;

    setBuffer(width, height);

    initRender(width, height);
    setWindow(width, height, cfg.title);

    char gradient[] = GRADIENT_0;
    size_t gradientSize = 0;
	setGradientSize(gradient, gradientSize);
	
    vec3 boxPos = vec3(0, 0, -2);
    vec3 planePos = vec3(0, 0, -3);
    vec3 light = vec3(0, 20, -7.0);

    std::vector<Object*> objects;
    objects.push_back(new Plane(planePos, vec3(0, 1, 0), 0.5f, Color::White()));
    
	Box* testBox = new Box(boxPos, vec3(2,2,2), 1.0f, Color::White());
    objects.push_back(testBox);

	HANDLE colorChangeThread = CreateThread(NULL, 0, changeBoxColor, testBox, 0, NULL);

    for (int t = 1; t > 0; ++t) {
        swapBuffers(currentBuffer, displayBuffer);

        for (int j = 0; j < height; ++j) {
            for (int i = 0; i < width; ++i) {
                float brightness = 1.0f;

                vec2 uv = createUV(i, j, width, height, aspect, pixelAspect);

                vec3 rd = norm(vec3(1, uv));
                vec3 ro = vec3(-7, 0, -1);

                renderObjects(objects, ro, rd, hit, currentcolor, brightness, normal, light);
                renderColor(i, j, width, gradientSize, gradient, hit, currentcolor, brightness);
            }
        }
        render(width, height);
    }

	WaitForSingleObject(colorChangeThread, INFINITE);
    freeBuffers();
    freeObjects(objects);

    return 0;
}
