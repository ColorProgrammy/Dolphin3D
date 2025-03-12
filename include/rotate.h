#pragma once

#include <cmath>
#include "functions.h"
#include "mat4.h"

mat4 transform;


inline vec3 rotateAroundCenterX(vec3 a, double angle)
{
	vec3 b = a;
	b.z = a.z * cos(float(angle)) - a.y * sin(float(angle));
	b.y = a.z * sin(float(angle)) + a.y * cos(float(angle));
	return b;
}

inline vec3 rotateAroundX(vec3 a, double angle, vec3 origin)
{
    vec3 b = a - origin;
    b.y = b.z * cos(float(angle)) - b.y * sin(float(angle));
    b.z = b.z * sin(float(angle)) + b.y * cos(float(angle));
    return b + origin;
}

inline vec3 rotateAroundCenterY(vec3 a, double angle)
{
	vec3 b = a;
	b.x = a.x * cos(float(angle)) - a.z * sin(float(angle));
	b.z = a.x * sin(float(angle)) + a.z * cos(float(angle));
	return b;
}

inline vec3 rotateAroundY(vec3 a, double angle, vec3 origin)
{
    vec3 b = a - origin;
    b.x = b.x * cos(float(angle)) - b.z * sin(float(angle));
    b.z = b.x * sin(float(angle)) + b.z * cos(float(angle));
    return b + origin;
}

inline vec3 rotateAroundCenterZ(vec3 a, double angle)
{
	vec3 b = a;
	b.x = a.x * cos(float(angle)) - a.y * sin(float(angle));
	b.y = a.x * sin(float(angle)) + a.y * cos(float(angle));
	return b;
}

inline vec3 rotateAroundZ(vec3 a, double angle, vec3 origin)
{
    vec3 b = a - origin;
    b.x = b.x * cos(float(angle)) - b.y * sin(float(angle));
    b.y = b.x * sin(float(angle)) + b.y * cos(float(angle));
    return b + origin;
}

inline mat4 getRotationMatrix() const {
    mat4 rotation = transform;
    
    rotation.m[0][3] = 0.0f;
    rotation.m[1][3] = 0.0f;
    rotation.m[2][3] = 0.0f;
    rotation.m[3][3] = 1.0f;
    return rotation;
}


inline void rotateLocalX(vec3 pos, float angle) {
	mat4 rotation = getRotationMatrix() * mat4::rotateX(angle);
	transform = mat4::translate(pos) * rotation;
}

inline void rotateLocalY(vec3 pos, float angle) {
	mat4 rotation = getRotationMatrix() * mat4::rotateY(angle);
	transform = mat4::translate(pos) * rotation;
}

inline void rotateLocalZ(vec3 pos, float angle) {
	mat4 rotation = getRotationMatrix() * mat4::rotateZ(angle);
	transform = mat4::translate(pos) * rotation;
}

inline void translate(mat4 transform, const vec3& t, vec3 pos) {
    transform = mat4::translate(t) * transform;
    pos += t;
}
