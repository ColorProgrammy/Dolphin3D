#pragma once
#include "Vector2.h"
#include "Vector3.h"

#include <cmath>
#include <iostream>

#ifndef M_PI
#define M_PI 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679
#endif

#pragma warning(push)
#pragma warning(disable : 4005)

#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

#pragma warning(pop)

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
    return vec3(static_cast<float>(sign(v.x)), static_cast<float>(sign(v.y)), static_cast<float>(sign(v.z)));
}

inline vec3 step(vec3 const& edge, vec3 v) {
    return vec3(static_cast<float>(step(edge.x, v.x)), 
                 static_cast<float>(step(edge.y, v.y)), 
                 static_cast<float>(step(edge.z, v.z)));
}

inline float dot(const vec3& a, const vec3& b) {
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

inline vec3 norm(vec3 v) {
	float len = length(v);
	if (len == 0.0f) return vec3(0.0f);
	return v / len;
}

inline float radians(float degrees) {
    return degrees * 3.14159265358979323846f / 180.0f;
}

inline float smoothstep(float edge0, float edge1, float x) {
    x = clamp((x - edge0) / (edge1 - edge0), 0.0f, 1.0f);
    return x * x * (3.0f - 2.0f * x);
}

inline float cross(const vec2& a, const vec2& b) {
	return a.x * b.y - a.y * b.x;
}

inline vec3 cross(const vec3& a, const vec3& b) {
	return vec3(
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x
	);
}
////////

// Visual functions

inline vec3 reflect(vec3 rd, vec3 n) {
	return rd - n * (2.0f * dot(n, rd));
}

////////

// Folder

static const GUID DOCUMENTS_FOLDER = 
    {0xFDD39AD0, 0x238F, 0x46AF, {0xAD, 0xB4, 0x6C, 0x85, 0x48, 0x03, 0x69, 0xC7}};

////////

// Other

inline std::string ws2s(const std::wstring& wstr) {
    int size_needed = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, NULL, 0, NULL, NULL);
    std::string strTo(size_needed, 0);
    WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, &strTo[0], size_needed, NULL, NULL);
    return strTo;
}

////////