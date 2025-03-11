#pragma once
#include "Vector2.h"
#include <cmath>
#include <stdexcept>

struct vec3
{
    float x, y, z;
    vec3() : x(0), y(0), z(0) {};

    float length() const {
        return std::sqrt(x * x + y * y + z * z);
    }

    inline float length(vec3 const& v) {
        return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    }

    inline float length(vec2 const& v) {
        return std::sqrt(v.x * v.x + v.y * v.y);
    }

    vec3 norm(vec3 v) {
        float len = length(v);
        if (len == 0.0f) return vec3(0.0f);
        return v / len;
    }

    vec3 norm() const {
        float len = length();
        if (len == 0.0f) return vec3(0.0f);
        return *this / len;
    }

    vec3(float _value) : x(_value), y(_value), z(_value) {};
    vec3(float _x, vec2 const& v) : x(_x), y(v.x), z(v.y) {};
    vec3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {};

    vec3 operator+(vec3 const& other) const { return vec3(x + other.x, y + other.y, z + other.z); }
    vec3 operator-(vec3 const& other) const { return vec3(x - other.x, y - other.y, z - other.z); }
    vec3 operator*(vec3 const& other) const { return vec3(x * other.x, y * other.y, z * other.z); }

    vec3 operator/(vec3 const& other) const {
        return vec3(x / other.x, y / other.y, z / other.z);
    }

    vec3 operator/(float scalar) const {
        if (scalar == 0.0f) {
            throw std::runtime_error("Division by zero");
        }
        return vec3(x / scalar, y / scalar, z / scalar);
    }

    vec3 operator-() const { return vec3(-x, -y, -z); }

    // Add the += operator
    vec3& operator+=(const vec3& other) {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }
};
