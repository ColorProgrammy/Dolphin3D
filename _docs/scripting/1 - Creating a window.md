# Creating a window

To work with the engine we need to create a window.

***Code:***

```cpp
#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>
#include <windows.h>
#include <conio.h>
#include "../include/Dolphin3D.h"

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

    vec3 light = vec3(0, 0, 0);

    std::vector<Object*> objects;

    for (int t = 1; t > 0; ++t) {
        swapBuffers(currentBuffer, displayBuffer, width, height);

        for (int j = 0; j < height; ++j) {
            for (int i = 0; i < width; ++i) {
                float brightness = 1.0f;

                vec2 uv = createUV(i, j, width, height);

                vec3 rd = norm(vec3(1, uv));
                vec3 ro = vec3(-7, 0, -1);		

                renderObjects(objects, ro, rd, hit, currentcolor, brightness, normal, light);
                renderColor(i, j, width, gradientSize, gradient, hit, currentcolor, brightness);
            }
        }
        render(width, height);
    }

    freeBuffers();
    freeObjects(objects);

    return 0;
}
```
