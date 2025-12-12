/*
File: collision.h
Developer: ColorProgrammy

Description:
Library with collision function (using the radius)
*/

#include "functions.h"

template <typename Callback>
void collision(vec3 pos1, vec3 pos2, float sphereRadius, Callback callback) {
    float distanceBetweenSpheres = length(pos1 - pos2);
    if (distanceBetweenSpheres <= 2 * sphereRadius) {
        callback();
    }
}