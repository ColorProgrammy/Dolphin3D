#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>
#include <windows.h>
#include <conio.h>
#include "../include/Dolphin3D.h"

int main() {
    int width = 100;
    int height = 30;

    setBuffer(width, height);
    initRender(width, height);
    setWindow(width, height, "Empty");
    system("cls");

    bool hit;
    Color currentcolor;
    vec3 normal;

    const char* gradientName = GRADIENT_0;
    size_t gradientSize = 0;
    const size_t maxGradientSize = 100;
    char gradient[maxGradientSize];
    setGradientSize(gradient, gradientSize, maxGradientSize, gradientName);

	std::vector<Light> lights;
	// Lights here

    std::vector<Object*> objects;
    // Objects here

    while (true) {
        swapBuffers(currentBuffer, displayBuffer, width, height);

        for (int j = 0; j < height; ++j) {
            for (int i = 0; i < width; ++i) {
                float brightness = 0.5f;

                vec2 uv = createUV(i, j, width, height);
                vec3 rd = norm(vec3(1, uv));
                vec3 ro = vec3(0, 0, -6);

                setObjects(objects, ro, rd, hit, currentcolor, brightness, normal, lights, 0.4f, 7.0f);
                setColors(i, j, width, gradientSize, gradient, hit, currentcolor, brightness);
            }
        }

        render(width, height, 30);
    }
    freeBuffers();
    freeObjects(objects);
    return 0;
}
