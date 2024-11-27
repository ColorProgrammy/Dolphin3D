/*
File: functions.h
Developer: ColorProgrammy

Description:
Functions for engine operation
*/

// Please do not change this code!

#pragma once
#include "Vector2.h" // ----\
                             |=== Vectors
#include "Vector3.h" // ----/
#include <cmath>
#include <algorithm>

// Mathematical functions

int clamp(int value, int min, int max) { 
    return std::max(std::min(value, max), min);
}

double sign(double a) { 
    return (0 < a) - (a < 0); 
}

double step(double edge, double x) {
    return x > edge;
}

float length(vec3 const& v) { 
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z); 
}

float length(vec2 const& v) { 
    return sqrt(v.x * v.x + v.y * v.y); 
}

vec3 abs(vec3 const& v) { 
    return vec3(fabs(v.x), fabs(v.y), fabs(v.z)); 
}

vec3 sign(vec3 const& v) { 
    return vec3(sign(v.x), sign(v.y), sign(v.z));
}

vec3 step(vec3 const& edge, vec3 v) {
    return vec3(step(edge.x, v.x), step(edge.y, v.y), step(edge.z, v.z)); 
}

float dot(vec3 const& a, vec3 const& b) { 
    return a.x * b.x + a.y * b.y + a.z * b.z; 
}

vec3 norm(vec3 v) { 
    return v / length(v); 
}

////////

// Visual functions

vec3 reflect(vec3 rd, vec3 n) { 
    return rd - n * (2 * dot(n, rd)); 
}

////////

// Objects

vec2 sphere(vec3 ro, vec3 rd, float r) {
    float b = dot(ro, rd);
    float c = dot(ro, ro) - r * r;
    float h = b * b - c;
    if (h < 0.0) return vec2(-1.0);
    h = sqrt(h);
    return vec2(-b - h, -b + h);
}

vec2 box(vec3 ro, vec3 rd, float baseWidth, float baseHeight, float boxHeight, vec3& outNormal) {
    vec3 boxSize = vec3(baseWidth, baseHeight, boxHeight);
    vec3 m = vec3(1.0) / rd;
    vec3 n = m * ro;
    vec3 k = abs(m) * boxSize;
    vec3 t1 = -n - k;
    vec3 t2 = -n + k;

    float tN = std::max(std::max(t1.x, t1.y), t1.z);
    float tF = std::min(std::min(t2.x, t2.y), t2.z);

    if (tN > tF || tF < 0.0) return vec2(-1.0);

    vec3 yzx = vec3(t1.y, t1.z, t1.x);
    vec3 zxy = vec3(t1.z, t1.x, t1.y);
    outNormal = -sign(rd) * step(yzx, t1) * step(zxy, t1);

    if (outNormal.z < 0) {
        vec3 slopeNormal = norm(vec3(-outNormal.x, -outNormal.y, 1));
        outNormal = slopeNormal;
    }

    return vec2(tN, tF);
}

float plane(vec3 ro, vec3 rd, vec3 p, float w) {
    return -(dot(ro, p) + w) / dot(rd, p);
}

////////

// Rotate

vec3 rotateX(vec3 a, double angle)
{
    vec3 b = a;
    b.z = a.z * cos(angle) - a.y * sin(angle);
    b.y = a.z * sin(angle) + a.y * cos(angle);
    return b;
}

vec3 rotateY(vec3 a, double angle)
{
    vec3 b = a;
    b.x = a.x * cos(angle) - a.z * sin(angle);
    b.z = a.x * sin(angle) + a.z * cos(angle);
    return b;
}

vec3 rotateZ(vec3 a, double angle)
{
    vec3 b = a;
    b.x = a.x * cos(angle) - a.y * sin(angle);
    b.y = a.x * sin(angle) + a.y * cos(angle);
    return b;
}

////////
