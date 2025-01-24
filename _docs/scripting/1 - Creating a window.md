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

Let's take a look at the code.

-----

First we import the Dolphin3D.h library and others.

```cpp
#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>
#include <windows.h>
#include <conio.h>
#include "../include/Dolphin3D.h"
```

---

Next we initialize `3` variables:

```cpp
bool hit;
Color currentcolor;
vec3 normal;
```

I won’t go into detail here, as we will discuss this in the following chapters.

-----

Next we import config.

```cpp
Config cfg = readConfig("config.ini");
```

**But what is it for?**

***It includes:***

```ini
[Window]
Title = Example
IconPath = assets/ufo.ico
Width = 100
Height = 30
```

It is used to easily change application data.

We specify a relative path and therefore we only have the file name.

-----

Now we will indicate the dimensions.

```cpp
int width = cfg.width;
int height = cfg.height;
```

As you can see, we do not specify numbers, but take them from `config.ini`

-----

