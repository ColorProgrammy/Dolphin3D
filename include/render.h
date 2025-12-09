#ifndef RENDER_H
#define RENDER_H

#include <windows.h>
#include <vector>
#include "color.h"
#include "Vector3.h"

class Object;

enum LightType {
    LIGHT_POINT,
    LIGHT_SPOT,
	LIGHT_DIRECTIONAL
};

struct Light {
    LightType type;
    vec3 position;
    vec3 direction;
    float intensity;
    float radius;
    float angle;

    Light(vec3 pos, float intens = 1.0f, float r = 5.0f)
        : type(LIGHT_POINT), position(pos), intensity(intens), radius(r), angle(0.0f), direction(vec3(0,0,0)) {}

    Light(vec3 pos, vec3 dir, float intens, float r, float ang)
        : type(LIGHT_SPOT), position(pos), direction(norm(dir)), intensity(intens), radius(r), angle(ang) {}
};

extern std::vector<Light> lights;
extern CHAR_INFO* currentBuffer;
extern CHAR_INFO* displayBuffer;

void setBuffer(int width, int height);
void freeBuffers();
void freeObjects(std::vector<Object*>& objects);
bool initRender(int width, int height);
void render(int width, int height, int fps = 60);
void setColors(int i, int j, int width, size_t gradientSize, const char* gradient, bool hit, Color currentcolor, float brightness);
void setObjects(std::vector<Object*>& objects, vec3& ro, vec3& rd, bool& hit, Color& currentcolor, float& brightness, vec3& normal, std::vector<Light>& lights, float shadowBrightness = 0.7f, float shadowDistance = 3.0f);
vec2 createUV(int i, int j, int width, int height);
void swapBuffers(CHAR_INFO* currentBuffer, CHAR_INFO* displayBuffer, int width, int height);
void createPointLight(std::vector<Light>& lights, vec3 position, float intensity = 1.0f, float radius = 3.0f);
void createSpotlight(std::vector<Light>& lights, vec3 position, vec3 direction, float intensity, float radius, float angle);
void createDirectionalLight(std::vector<Light>& lights, vec3 position, vec3 direction, float intensity = 1.0f, float width = 1.0f, float range = 10.0f);

#endif