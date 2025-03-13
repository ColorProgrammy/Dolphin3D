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
    setWindow(width, height, "Dolphin3D Demo");
    system("cls");

    size_t gradientSize = 0;
    const size_t maxGradientSize = 100;
    char gradient[maxGradientSize];

    setGradientSize(gradient, gradientSize, maxGradientSize, GRADIENT_0);

    std::vector<Object*> objects;

    vec3 planePos = vec3(0, 0, -5);
    objects.push_back(new Plane(planePos, vec3(0, 1, 0), 1.5f, Color::Green()));

    vec3 boxPos = vec3(-5, 0, -4);
    Box* box = new Box(boxPos, vec3(2.0f, 2.0f, 1.0f), 3.5f, Color::Blue());
    objects.push_back(box);

	vec3 boxPos1 = vec3(0, 3, -5);
    Box* box1 = new Box(boxPos1, vec3(1.0f, 3.0f, 1.0f), 3.5f, Color::Yellow());
    objects.push_back(box1);

    objects.push_back(new Box(vec3(0, 0, 0), vec3(1.0f, 3.0f, 1.0f), 5.5f, Color::White()));

    vec3 light = vec3(0, 500, -5);

	int io = 1;

    while (true) {
        swapBuffers(currentBuffer, displayBuffer, width, height);
		io += 1;

		box->rotateLocalY(0.05f);
		box->rotateLocalZ(0.02f);

		box1->rotateLocalX(0.02f);
		box1->rotateLocalZ(0.08f);

        for (int j = 0; j < height; ++j) {
            for (int i = 0; i < width; ++i) {
                float brightness = 0.2f;

                vec2 uv = createUV(i, j, width, height);
                vec3 rd = norm(vec3(1, uv));
                vec3 ro = vec3(-11, 0, -2);

                rd = rotateAroundCenterY(rd, 0.5f);
                ro = rotateAroundCenterY(ro, 0.5f);

				rd = rotateAroundCenterZ(rd, io * 0.03f);
                ro = rotateAroundCenterZ(ro, io * 0.03f);

                bool hit = false;
                Color currentcolor;
                vec3 normal;
                setObjects(objects, ro, rd, hit, currentcolor, brightness, normal, light, 0.7f, 2);

                setColors(i, j, width, gradientSize, gradient, hit, currentcolor, brightness);
            }
        }

        render(width, height, 60);

        if (_kbhit()) {
            char key = _getch();
            if (key == KEY_ESC) {
                break;
            }
        }
    }

    freeBuffers();
    freeObjects(objects);
    return 0;
}
