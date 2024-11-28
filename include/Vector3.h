/*
File: Vector3.h
Developer: ColorProgrammy

Description:
Creating Vector3
*/

// Please do not touch this code.

#include "Vector2.h"

struct vec3
{
    float x, y, z;

    vec3(float _value) : x(_value), y(_value), z(_value) {};
    vec3(float _x, vec2 const& v) : x(_x), y(v.x), z(v.y) {};
    vec3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {};

    vec3 operator+(vec3 const& second) { 
        return vec3(x + second.x, y + second.y, z + second.z); 
    }

    vec3 operator-(vec3 const& second) { 
        return vec3(x - second.x, y - second.y, z - second.z); 
    }

    vec3 operator*(vec3 const& second) { 
        return vec3(x * second.x, y * second.y, z * second.z); 
    }

    vec3 operator/(vec3 const& second) { 
        return vec3(x / second.x, y / second.y, z / second.z); 
    }

    vec3 operator-() {
        return vec3(-x, -y, -z); 
    }
};
