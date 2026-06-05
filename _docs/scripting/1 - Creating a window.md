# Creating a window

This guide walks you through a minimal window example that initializes the engine, sets up buffers, a gradient, an empty scene (no objects), and runs an infinite render loop.

## Full Code

```cpp
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
    setWindow(width, height, "Sample");
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
```

**Well then, let's get started!**

### Headers
```cpp
#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>
#include <windows.h>
#include <conio.h>
#include "../include/Dolphin3D.h"
```
It's simple here. We're including the libraries we need for work, as well as our framework. It's important to note the `"../"` part because the folder is located within the project folder, so we'll need to navigate up the path.

### Initialize the engine
```cpp
int main() {
    int width = 100;
    int height = 30;

    setBuffer(width, height);
    initRender(width, height);
    setWindow(width, height, "Sample");
    system("cls");
```
We optionally specify the screen resolution in characters (not pixels, this is important!). And then we initialize our engine.

`setBuffer` – allocates two buffers (current and display) of size _width * height_.

`initRender` – initializes internal renderer structures.

`setWindow` – creates the console window with the given title.

`system("cls")` – optional, clears system outputs during initialization.

```cpp
bool hit;
Color currentcolor;
vec3 normal;
```
We initialize the necessary variables for rendering, we can’t do without them, yea

```cpp
const char* gradientName = GRADIENT_0;
size_t gradientSize = 0;
const size_t maxGradientSize = 100;
char gradient[maxGradientSize];
setGradientSize(gradient, gradientSize, maxGradientSize, gradientName);
```
Here we initialize the symbol gradient to simulate brightness. The built-in GRADIENT_0 is used here, but you can add your own.

`setGradientSize(...)` – sets the gradient size for brightness to work properly

### Objects and lights
```cpp
std::vector<Light> lights;
// Lights here

std::vector<Object*> objects;
// Objects here
```
Here you can add your own objects and lights. We'll cover these in another section.

### Main loop
```cpp
while (true) {
    swapBuffers(currentBuffer, displayBuffer, width, height);
```
And so we begin our loop. And yes, it's infinite. However, we'll be interrupting it when we exit, so everything's fine.

`swapBuffer` exchanges the two buffers – the engine renders into `currentBuffer`, while `displayBuffer` is shown on screen. Prevents flickering (double buffering).

```cpp
for (int j = 0; j < height; ++j) {
    for (int i = 0; i < width; ++i) {
        float brightness = 0.5f;

        vec2 uv = createUV(i, j, width, height);
        vec3 rd = norm(vec3(1, uv));
        vec3 ro = vec3(0, 0, -6);
```
This is where things get more difficult to understand, let's break it down.

Outer loop over rows (`j`), inner loop over columns (`i`). For each screen position, compute color and brightness.

`uv` – normalized pixel coordinates (usually in [0,1] or [-1,1] depending on createUV).

`rd` – ray direction. `vec3(1, uv)` means X = 1, Y = uv.x, Z = uv.y, then normalized.

`ro` – ray origin. Camera positioned at (0, 0, -6) looking toward positive Z.

You don't need to understand this too much. The main thing to remember is that you can change the camera's position (using `ray origin`).

```cpp
setObjects(objects, ro, rd, hit, currentcolor, brightness, normal, lights, 0.4f, 7.0f);
setColors(i, j, width, gradientSize, gradient, hit, currentcolor, brightness);
```
setObjects iterates over all objects in objects and finds the closest intersection with the ray (ro, rd).

If an intersection is found: hit = true, currentcolor and normal are set, and brightness is updated with lighting from lights.

The last two arguments (0.4f, 7.0f) are ...

Since both objects and lights are empty, no intersection occurs → hit remains false
