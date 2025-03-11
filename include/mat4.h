// mat4.h
#pragma once
#include "Vector3.h"
#include "Vector4.h"

struct mat4 {
    float m[4][4];

    mat4() { 
        memset(m, 0, sizeof(m)); 
        m[0][0] = m[1][1] = m[2][2] = m[3][3] = 1.0f;
    }

    // Умножение матриц
    mat4 operator*(const mat4& right) const {
        mat4 result;
        for(int i = 0; i < 4; ++i) {
            for(int j = 0; j < 4; ++j) {
                result.m[i][j] = 0;
                for(int k = 0; k < 4; ++k)
                    result.m[i][j] += m[i][k] * right.m[k][j];
            }
        }
        return result;
    }

    // Умножение на вектор (для точек)
    vec3 operator*(const vec3& v) const {
        vec4 result(
            m[0][0]*v.x + m[0][1]*v.y + m[0][2]*v.z + m[0][3],
            m[1][0]*v.x + m[1][1]*v.y + m[1][2]*v.z + m[1][3],
            m[2][0]*v.x + m[2][1]*v.y + m[2][2]*v.z + m[2][3],
            m[3][0]*v.x + m[3][1]*v.y + m[3][2]*v.z + m[3][3]
        );
        return vec3(result.x/result.w, result.y/result.w, result.z/result.w);
    }

    static mat4 identity() { return mat4(); }

    static mat4 translate(const vec3& t) {
        mat4 m;
        m.m[0][3] = t.x;
        m.m[1][3] = t.y;
        m.m[2][3] = t.z;
        return m;
    }

    static mat4 rotateX(float angle) {
        mat4 m;
        float c = cos(angle), s = sin(angle);
        m.m[1][1] = c;  m.m[1][2] = -s;
        m.m[2][1] = s;  m.m[2][2] = c;
        return m;
    }

    static mat4 rotateY(float angle) {
        mat4 m;
        float c = cos(angle), s = sin(angle);
        m.m[0][0] = c;  m.m[0][2] = s;
        m.m[2][0] = -s; m.m[2][2] = c;
        return m;
    }

    static mat4 rotateZ(float angle) {
        mat4 m;
        float c = cos(angle), s = sin(angle);
        m.m[0][0] = c;  m.m[0][1] = -s;
        m.m[1][0] = s;  m.m[1][1] = c;
        return m;
    }
	mat4 inverse() const {
		mat4 inv;
		// Транспонирование матрицы поворота 3x3
		for (int i = 0; i < 3; ++i)
			for (int j = 0; j < 3; ++j)
				inv.m[i][j] = m[j][i];
	    
		// Обратный перенос
		inv.m[0][3] = -(m[0][0]*m[0][3] + m[1][0]*m[1][3] + m[2][0]*m[2][3]);
		inv.m[1][3] = -(m[0][1]*m[0][3] + m[1][1]*m[1][3] + m[2][1]*m[2][3]);
		inv.m[2][3] = -(m[0][2]*m[0][3] + m[1][2]*m[1][3] + m[2][2]*m[2][3]);
		return inv;
	}

    // Поворот вектора (без учета переноса)
    vec3 rotateVector(const vec3& v) const {
        return vec3(
            m[0][0]*v.x + m[0][1]*v.y + m[0][2]*v.z,
            m[1][0]*v.x + m[1][1]*v.y + m[1][2]*v.z,
            m[2][0]*v.x + m[2][1]*v.y + m[2][2]*v.z
        );
    }
};