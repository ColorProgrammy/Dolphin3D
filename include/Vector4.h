#pragma once
#include "Vector3.h"
#include <cmath>
#include <stdexcept> // Include for std::runtime_error

struct vec4
{
    float x, y, z, w;

    vec4() : x(0), y(0), z(0), w(0) {};

    float length() const {
        return std::sqrt(x * x + y * y + z * z + w * w);
    }

    vec4 norm() const {
        float len = length();
        if (len == 0.0f) return vec4(0.0f);
        return *this / len; // This will now work if the operator is defined
    }

    vec4(float _value) : x(_value), y(_value), z(_value), w(_value) {};
    vec4(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {};
    vec4(float _x, vec3 const& v, float _w) : x(_x), y(v.x), z(v.y), w(_w) {};

    vec4 operator+(vec4 const& other) const { return vec4(x + other.x, y + other.y, z + other.z, w + other.w); }
    vec4 operator-(vec4 const& other) const { return vec4(x - other.x, y - other.y, z - other.z, w - other.w); }
    vec4 operator*(vec4 const& other) const { return vec4(x * other.x, y * other.y, z * other.z, w * other.w); }

    // Overload for dividing a vec4 by a vec4
    vec4 operator/(vec4 const& other) const {
        return vec4(x / other.x, y / other.y, z / other.z, w / other.w);
    }

    // Overload for dividing a vec4 by a scalar (float)
    vec4 operator/(float scalar) const {
        if (scalar == 0.0f) {
            throw std::runtime_error("Division by zero");
        }
        return vec4(x / scalar, y / scalar, z / scalar, w / scalar);
    }

    vec4 operator-() const { return vec4(-x, -y, -z, -w); }
};