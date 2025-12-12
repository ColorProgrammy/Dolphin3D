/*
File: rotate.h
Developer: ColorProgrammy

Description:
Header file for rotating objects around axes
(not including rotation around their own axis, which is written in mat4.h)
*/

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