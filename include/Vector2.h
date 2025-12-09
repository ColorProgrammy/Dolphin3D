/*
File: Vector2.h
Developer: ColorProgrammy

Description:
Creating Vector2
*/

// Please do not touch this code.

#pragma once

#include <cmath>

struct vec2
{
    float x, y;

    vec2(float value) : x(value), y(value) {}
    vec2(float _x, float _y) : x(_x), y(_y) {}

    float length() const {
        return std::sqrt(x * x + y * y);
    }
	
	inline float length(vec2 const& v) {
		return std::sqrt(v.x * v.x + v.y * v.y);
	}

    vec2 operator/(float scalar) const {
        if (scalar == 0.0f) {
            throw std::runtime_error("Division by zero");
        }
        return vec2(x / scalar, y / scalar);
    }

    vec2 operator+(vec2 const& other) const { 
        return vec2(x + other.x, y + other.y); 
    }

    vec2 operator-(vec2 const& other) const { 
        return vec2(x - other.x, y - other.y); 
    }

    vec2 operator*(vec2 const& other) const { 
        return vec2(x * other.x, y * other.y); 
    }

    vec2 operator/(vec2 const& other) const { 
        return vec2(x / other.x, y / other.y); 
    }

    vec2 operator-() const { 
        return vec2(-x, -y); 
    }

    vec2& operator+=(const vec2& other) {
        x += other.x;
        y += other.y;
        return *this;
    }
    
    vec2& operator-=(const vec2& other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }
};