/*
File: Vector2.h
Developer: ColorProgrammy

Description:
Creating Vector2
*/

// Please do not touch this code.

#pragma once

struct vec2
{
    float x, y;

    vec2(float value) : x(value), y(value) {}
    vec2(float _x, float _y) : x(_x), y(_y) {}

    vec2 operator+(vec2 const& second) { 
        return vec2(x + second.x, y + second.y); 
    }

    vec2 operator-(vec2 const& second) { 
        return vec2(x - second.x, y - second.y); 
    }

    vec2 operator*(vec2 const& second) {
        return vec2(x * second.x, y * second.y);
    }

    vec2 operator/(vec2 const& second) { 
        return vec2(x / second.x, y / second.y); 
    }
};
