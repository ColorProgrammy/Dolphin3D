/*
File: camera.h
Developer: ColorProgrammy

Description:
A class for local object rotations
*/

#include "mat4.h"

class Camera {
private:
    vec3 position;
    mat4 transform;

public:
    Camera(const vec3& pos) : position(pos) {
        transform = mat4::identity();
    }

    void rotateLocalX(float angle) {
        mat4 rotation = mat4::rotateX(angle);
        transform = transform * rotation;
    }

    void rotateLocalY(float angle) {
        mat4 rotation = mat4::rotateY(angle);
        transform = transform * rotation;
    }

    void rotateLocalZ(float angle) {
        mat4 rotation = mat4::rotateZ(angle);
        transform = transform * rotation;
    }

    vec3 getPosition() const {
        return transform * position;
    }

    vec3 getRayDirection(const vec3& localDir) const {
        return transform.rotateVector(localDir);
    }
};