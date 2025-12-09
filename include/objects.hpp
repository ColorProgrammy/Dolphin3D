#pragma once
#include "functions.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "mat4.h"
#include "color.h"
#include <memory>

inline vec2 sphere(vec3 ro, vec3 rd, float r) {
	float b = dot(ro, rd);
	float c = dot(ro, ro) - r * r;
	float h = b * b - c;
	if (h < 0.0f) return vec2(-1.0f);
	h = sqrt(h);
	return vec2(-b - h, -b + h);
}

inline vec2 box(vec3 ro, vec3 rd, float baseWidth, float baseHeight, float boxHeight, vec3& outNormal) {
    vec3 boxSize = vec3(baseWidth, baseHeight, boxHeight);
    vec3 m = vec3(1.0) / rd;
    vec3 n = m * ro;
    vec3 k = abs(m) * boxSize;
    vec3 t1 = -n - k;
    vec3 t2 = -n + k;

    float tN = max(max(t1.x, t1.y), t1.z);
    float tF = min(min(t2.x, t2.y), t2.z);

    if (tN > tF || tF < 0.0) return vec2(-1.0);

    vec3 yzx = vec3(t1.y, t1.z, t1.x);
    vec3 zxy = vec3(t1.z, t1.x, t1.y);
    outNormal = -sign(rd) * step(yzx, t1) * step(zxy, t1);

    outNormal = norm(outNormal);

    if (outNormal.z < 0) {
        vec3 slopeNormal = norm(vec3(-outNormal.x, -outNormal.y, 1));
        outNormal = slopeNormal;
    }

    return vec2(tN, tF);
}

inline float plane(vec3 ro, vec3 rd, vec3 p, float w) {
	return -(dot(ro, p) + w) / dot(rd, p);
}

inline vec2 elipsoid(vec3 ro, vec3 rd, vec3 ra) {
	vec3 ocn = ro / ra;
	vec3 rdn = rd / ra;
	float a = dot(rdn, rdn);
	float b = dot(ocn, rdn);
	float c = dot(ocn, ocn);
	float h = b * b - a * (c - 1.0f);
	if (h < 0.0f) return vec2(-1.0f);
	h = sqrt(h);
	return vec2(-b - h,-b + h) / a;
}

inline vec3 elipNormal(vec3 pos, vec3 ra) {
	return norm(pos / (ra * ra));
}

inline float capIntersect(vec3 ro, vec3 rd, vec3 pa, vec3 pb, float ra ) {
	vec3 ba = pb - pa;
	vec3 oa = ro - pa;
	float baba = dot(ba, ba);
	float bard = dot(ba, rd);
	float baoa = dot(ba, oa);
	float rdoa = dot(rd, oa);
	float oaoa = dot(oa, oa);
	float a = baba - bard * bard;
	float b = baba * rdoa - baoa * bard;
	float c = baba * oaoa - baoa * baoa - ra * ra * baba;
	float h = b * b - a * c;
	if (h >= 0.0f)
	{
	float t = (-b - sqrt(h)) / a;
	float y = baoa + t * bard;
	if (y > 0.0f && y < baba) return t;

		vec3 oc = (y <= 0.0f) ? oa : ro - pb;
		b = dot(rd, oc);
		c = dot(oc, oc) - ra * ra;
		h = b * b - c;
		if(h > 0.0f) return -b - sqrt(h);
	}
	return -1.0f;
}

inline vec4 cylIntersect(const vec3& ro, const vec3& rd, const vec3& a, const vec3& b, float ra) {
    vec3 ba = b - a;
    vec3 oc = ro - a;
    float baba = dot(ba, ba);
    float bard = dot(ba, rd);
    float baoc = dot(ba, oc);
    float k2 = baba - bard * bard;
    float k1 = baba * dot(oc, rd) - baoc * bard;
    float k0 = baba * dot(oc, oc) - baoc * baoc - ra * ra * baba;
    float h = k1 * k1 - k2 * k0;
    if (h < 0.0f) return vec4(-1.0f, 0.0f, 0.0f, 0.0f);
    h = std::sqrt(h);
    float t = (-k1 - h) / k2;
    float y = baoc + t * bard;
    if (y > 0.0f && y < baba) {
        vec3 intersection = oc + rd * t - ba * (y / baba);
        return vec4(t, intersection.x / ra, intersection.y / ra, intersection.z / ra);
    }
    t = ((y < 0.0f) ? 0.0f : baba - baoc) / bard;
    if (std::abs(k1 + k2 * t) < h) {
        vec3 normal = static_cast<vec3>(ba) * static_cast<float>(sign(y)) / static_cast<float>(std::sqrt(baba));
        return vec4(t, normal.x, normal.y, normal.z);
    }
    return vec4(-1.0f, 0.0f, 0.0f, 0.0f);
}

inline vec3 cylNormal(const vec3& p, const vec3& a, const vec3& b, float ra) {
    vec3 pa = p - a;
    vec3 ba = b - a;
    float baba = dot(ba, ba);
    float paba = dot(pa, ba);
    float h = paba / baba;
    return (pa - ba * h) / ra;
}

class Object {
protected:
    mat4 transform; // Transformation matrix of the object.
    vec3 pos;       // Position of the object.

public:
    float albedo;
    Color color;

    Object() : albedo(0.0f), color(Color::White()), pos(vec3(0, 0, 0)) {
        transform = mat4::identity(); // Initialize to identity matrix
    }

    Object(float albedo, const Color& color = Color::White(), const vec3& position = vec3(0, 0, 0))
        : albedo(albedo), color(color), pos(position) {
        transform = mat4::identity(); // Initialize
        setPosition(position); // Set initial position.
    }

    virtual bool set(vec3 ro, vec3 rd, float& dist, vec3& n) = 0;
    virtual ~Object() {}

    virtual float getAlbedo() const { return albedo; }
    virtual Color getColor() const { return color; }

    virtual void setPosition(const vec3& position) {
        // Instead of calculating the difference, create a translation matrix directly to the new position.
        transform = mat4::translate(position) *  getRotationMatrix();  // IMPORTANT: Preserve rotation
        pos = position;
    }

	mat4 getRotationMatrix() const {
		mat4 rotation = transform;
		rotation.m[0][3] = 0.0f;
		rotation.m[1][3] = 0.0f;
		rotation.m[2][3] = 0.0f;
		return rotation;
	}

    virtual void setColor(const Color& color) {
        this->color = color;
    }

    void rotateLocalX(float angle) {
        mat4 rotation = mat4::rotateX(angle);
        // Preserve existing translation and apply new rotation
        transform = mat4::translate(pos) * rotation * getRotationMatrix();
    }

    void rotateLocalY(float angle) {
        mat4 rotation = mat4::rotateY(angle);
        transform = mat4::translate(pos) * rotation * getRotationMatrix();
    }

    void rotateLocalZ(float angle) {
        mat4 rotation = mat4::rotateZ(angle);
        transform = mat4::translate(pos) * rotation * getRotationMatrix();
    }

    

    vec3 getPosition() const {
        return pos; // Return the object's position
    }
};

class Box : public Object {
private:
    vec3 size;
    float dist;
    vec3 n;

public:
    Box(vec3 pos, vec3 size, float albedo, const Color& color = Color::White())
        : Object(albedo, color, pos), size(size) {}

    bool Box::set(vec3 ro, vec3 rd, float& dist, vec3& n) {
		mat4 invTransform = transform.inverse();
		vec3 localRo = invTransform * ro;
		vec3 localRd = invTransform.rotateVector(rd);

		vec2 intersection = box(localRo, localRd, size.x, size.y, size.z, n);
		if (intersection.x > 0 && intersection.x < dist) {
			dist = intersection.x;
			n = norm(transform.rotateVector(n));
			return true;
		}
		return false;
	}

    void setColor(const Color& color) override {
        this->color = color;
    }

    vec3 getPos() const { return pos; }
    vec3 getSize() const { return size; }
};

class Plane : public Object {
public:
    vec3 pos;
    vec3 n;
    float dist;

public:
    Plane() : pos(), n(), dist(10000.0f), Object() {}
    Plane(vec3 pos, vec3 n, float albedo, const Color& color = Color::White())
        : pos(pos), n(n), dist(10000.0f), Object(albedo, color) {}

    bool set(vec3 ro, vec3 rd, float& dist, vec3& n) override {
        float intersection = plane(ro, rd, pos, 0.0f);
        if (intersection > 0 && intersection < dist) {
            dist = intersection;
            n = this->n;
            return true;
        }
        return false;
    }

    vec3 getPos() const { return pos; }
    vec3 getN() const { return n; }

    void setPosition(const vec3& pos) override {
        this->pos = pos;
    }

	void setColor(const Color& color) override {
        this->color = color;
    }
};

class Sphere : public Object {
private:
    vec3 pos;
    float radius;
    float dist;
    vec3 n;

public:
    Sphere() : pos(), radius(0), dist(10000.0f), n(), Object() {}
    Sphere(vec3 pos, float radius, float albedo, const Color& color = Color::White())
        : pos(pos), radius(radius), dist(10000.0f), n(), Object(albedo, color) {}

    bool set(vec3 ro, vec3 rd, float& dist, vec3& n) override {
        vec2 intersection = sphere(ro - pos, rd, radius);
        if (intersection.x > 0 && intersection.x < dist) {
            dist = intersection.x;
            vec3 itPoint = ro - pos + rd * dist;
            n = norm(itPoint);
            return true;
        }
        return false;
    }

    void setPosition(const vec3& pos) override {
        this->pos = pos;
    }

	void setColor(const Color& color) override {
        this->color = color;
    }

    vec3 getPos() const { return pos; }
    float getRadius() const { return radius; }
};

class Elipsoid : public Object {
private:
    vec3 pos;
    vec3 radius;
    float dist;
    vec3 n;

public:
    Elipsoid() : pos(), radius(), dist(10000.0f), n(), Object() {}
    Elipsoid(vec3 pos, vec3 radius, float albedo, const Color& color = Color::White())
        : pos(pos), radius(radius), dist(10000.0f), n(), Object(albedo, color) {}

    bool set(vec3 ro, vec3 rd, float& dist, vec3& n) override {
        vec2 intersection = elipsoid(ro - pos, rd, radius);

        if (intersection.x > 0 && intersection.x < dist) {
            dist = intersection.x;
            n = elipNormal(ro + rd * intersection.x - pos, radius);
            return true;
        }
        return false;
    }

    void setPosition(const vec3& pos) override {
        this->pos = pos;
    }

	void setColor(const Color& color) override {
        this->color = color;
    }

    vec3 getPos() const { return pos; }
    vec3 getRadius() const { return radius; }
};

class Cap : public Object {
private:
    vec3 pa;
    vec3 pb;
    float radius;
    float dist;
    vec3 n;

public:
    Cap() : pa(), pb(), radius(0), dist(10000.0f), n(), Object() {}
    Cap(vec3 pa, vec3 pb, float radius, float albedo, const Color& color = Color::White())
        : pa(pa), pb(pb), radius(radius), dist(10000.0f), n(), Object(albedo, color) {}

   
    bool set(vec3 ro, vec3 rd, float& dist, vec3& n) override {
        float intersection = capIntersect(ro, rd, pa, pb, radius);
        if (intersection > 0 && intersection < dist) {
            dist = intersection;
            vec3 itPoint = ro + rd * dist;
            n = norm(itPoint - pa);
            return true;
        }
        return false;
    }

	void setColor(const Color& color) override {
        this->color = color;
    }

    void setPosition(const vec3& pos) override {
        this->pa = pos;
    }

    vec3 getPa() const { return pa; }
    vec3 getPb() const { return pb; }
    float getRadius() const { return radius; }
};

class Cylinder : public Object {
private:
    vec3 a;
    vec3 b;
    float radius;
    float dist;
    vec3 n;

public:
    Cylinder() : a(), b(), radius(0), dist(10000.0f), n(), Object() {}
    Cylinder(vec3 a, vec3 b, float radius, float albedo, const Color& color = Color::White())
        : a(a), b(b), radius(radius), dist(10000.0f), n(), Object(albedo, color) {}

    bool set(vec3 ro, vec3 rd, float& dist, vec3& n) override {
        vec4 intersection = cylIntersect(ro, rd, a, b, radius);
        if (intersection.x > 0 && intersection.x < dist) {
            dist = intersection.x;
            n = vec3(intersection.y, intersection.z, intersection.w);
            return true;
        }

        float t = capIntersect(ro, rd, a, b, radius);
        if (t > 0 && t < dist) {
            dist = t;
            vec3 itPoint = ro + rd * dist;
            n = norm(itPoint - a);
            return true;
        }

        t = capIntersect(ro, rd, b, a, radius);
        if (t > 0 && t < dist) {
            dist = t;
            vec3 itPoint = ro + rd * dist;
            n = norm(itPoint - b);
            return true;
        }

        return false;
    }

    void setPosition(const vec3& pos) override {
        this->a = pos;
    }

	void setColor(const Color& color) override {
        this->color = color;
    }

    vec3 getA() const { return a; }
    vec3 getB() const { return b; }
    float getRadius() const { return radius; }
};