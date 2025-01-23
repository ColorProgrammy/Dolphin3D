#ifndef RENDER_H
#define RENDER_H

#include <windows.h>
#include <vector>
#include "color.h"
#include "Vector3.h"

class Object;

// Function declaration, use extern to ensure a single definition in source file.
extern CHAR_INFO* currentBuffer;
extern CHAR_INFO* displayBuffer;

void setBuffer(int width, int height);
void freeBuffers();
void freeObjects(std::vector<Object*>& objects);
bool initRender(int width, int height);
void render(int width, int height);
void renderColor(int i, int j, int width, size_t gradientSize, const char* gradient, bool hit, Color currentcolor, float brightness);
void renderObjects(std::vector<Object*>& objects, vec3& ro, vec3& rd, bool& hit, Color& currentcolor, float& brightness, vec3& normal, vec3& light);
vec2 createUV(int i, int j, int width, int height);
void swapBuffers(CHAR_INFO* currentBuffer, CHAR_INFO* displayBuffer, int width, int height);

#endif
