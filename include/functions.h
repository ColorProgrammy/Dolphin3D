#pragma once

#include "Vector2.h"
#include "Vector3.h"

#include <math.h>
#include <stdio.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

// Mathematical functions

inline int clamp(int value, int min1, int max1) {
	return max(min(value, max1), min1);
}

inline double sign(double a) {
	return (0 < a) - (a < 0);
}

inline double step(double edge, double x) {
	return x > edge;
}

inline float length(vec3 const& v) {
	return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

inline float length(vec2 const& v) {
	return sqrt(v.x * v.x + v.y * v.y);
}

inline vec3 abs(vec3 const& v) {
	return vec3(fabs(v.x), fabs(v.y), fabs(v.z));
}

inline vec3 sign(vec3 const& v) {
	return vec3(sign(v.x), sign(v.y), sign(v.z));
}

inline vec3 step(vec3 const& edge, vec3 v) {
	return vec3(step(edge.x, v.x), step(edge.y, v.y), step(edge.z, v.z));
}

inline float dot(const vec3& a, const vec3& b) {
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

inline vec3 norm(vec3 v) {
	float len = length(v);
	if (len == 0.0f) return vec3(0.0f);
	return v / len;
}

////////

// Visual functions

inline vec3 reflect(vec3 rd, vec3 n) {
	return rd - n * (2.0f * dot(n, rd));
}

////////
