#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>
#include <windows.h>
#include <conio.h>
#include "src/../include/dolphin.h"

int main() {
    bool hit;
    Color currentcolor;
    vec3 normal;

    int width = 150;
    int height = 30;

    float aspect = (float)width / height;
    float pixelAspect = 8.0f / 16.0f;

    setBuffer(width, height);

    initRender(width, height);
    setWindow(width, height, "Title");

    char gradient[] = " .,:!/rH$#@";
    size_t gradientSize = strlen(gradient) - 1;
    
    vec3 light = vec3(0, 20, -7.0);
    // add positions here

    std::vector<Object*> objects;
    // create objects here
    
    for (int t = 1; t > 0; ++t) {
        std::swap(currentBuffer, displayBuffer);

        for (int j = 0; j < height; ++j) {
            for (int i = 0; i < width; ++i) {
                float brightness = 1.0f;

                vec2 uv = createUV(i, j, width, height, aspect, pixelAspect);

                vec3 rd = norm(vec3(1, uv));
                vec3 ro = vec3(-7, 0, -1);

                renderObjects(objects, ro, rd, hit, currentcolor, brightness, normal, light, 1.0f);
                renderColor(i, j, width, gradientSize, gradient, hit, currentcolor, brightness);
            }
        }
        render(width, height);
    }
    freeBuffers();
    freeObjects(objects);

    return 0;
}
