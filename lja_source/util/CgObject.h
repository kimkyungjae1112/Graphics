#pragma once
#ifndef __CG_OBJECT_H__
#define __CG_OBJECT_H__

#include "MyMatrix.h"
#include <ostream>
#include <memory>

using namespace jangan_lee_my_matrix;

class CgObject;

class Color {
public:
	double r;
	double g;
	double b;

	const static Color error;
	const static Color black;
	const static Color grey;
	const static Color white;
	const static Color red;
	const static Color green;
	const static Color blue;
	const static Color yellow;
	const static Color magenta;
	const static Color cyan;
	static Color of(const char* name);

	template<typename T1, typename T2, typename T3> Color(T1&& r, T2&& g, T3&& b) : r(std::forward<T1>(r)), g(std::forward<T2>(g)), b(std::forward<T3>(b)) {
		if (r <= 0) r = 0;
		if (r >= 1) r = 1;
		if (g <= 0) g = 0;
		if (g >= 1) g = 1;
		if (b <= 0) b = 0;
		if (b >= 1) b = 1;
	}
	Color() : Color(0.0, 0.0, 0.0) {}
	Color(const Color& rhs) : r(rhs.r), g(rhs.g), b(rhs.b) {}
	Color(Color&& rhs) noexcept : r(std::move(rhs.r)), g(std::move(rhs.g)), b(std::move(rhs.b)) {}
	Color& operator=(const Color& rhs) {
		this->r = rhs.r;
		this->g = rhs.g;
		this->b = rhs.b;
		return *this;
	}	
	Color& operator=(Color&& rhs) noexcept {
		this->r = std::move(rhs.r);
		this->g = std::move(rhs.g);
		this->b = std::move(rhs.b);
		return *this;
	}

	inline bool operator==(const Color& c) const {
		return r == c.r && g == c.g && b == c.b;
	}
	inline bool operator!=(const Color& c) const {
		return !(*this == c);
	}
	inline Color operator*(const Color& rhs) {
		return Color(r * rhs.r, g * rhs.g, b * rhs.b);
	}
	inline Color operator*(double ratio) const {
		return Color(r * ratio, g * ratio, b * ratio);
	}
	friend Color operator*(double ratio, const Color& c);
	friend std::ostream& operator<<(std::ostream& os, const Color& obj);
};

class Ray {
public:
	Vector4d source;
	Vector4d direction;

	template <typename V1, typename V2> Ray(V1&& source, V2&& direction) :
		source(std::forward<V1>(source)), 
		direction(std::forward<V2>(direction)) {}
	Ray(const Ray& rhs) : source(rhs.source), direction(rhs.direction) {}
	Ray(Ray&& rhs) noexcept : source(std::move(rhs.source)), direction(std::move(rhs.direction)) {}
	inline Ray& operator=(const Ray& rhs) {
		this->source = rhs.source;
		this->direction = rhs.direction;
		return *this;
	}
	inline Ray& operator=(Ray&& rhs) noexcept {
		this->source = std::move(rhs.source);
		this->direction = std::move(rhs.direction);
		return *this;
	}

	Vector4d GetPointBy(const double t_value) const;
	friend std::ostream& operator<<(std::ostream& os, const Ray& obj);
};

class RaycastHitInfo {
public:
	bool is_hit;
	double t_value;
	Vector4d hit_position;
	Color color;
	Vector4d normal;
	const CgObject* hit_object;

	const static RaycastHitInfo no_hit;

	template <typename t1, typename t2, typename t3, typename t4, typename t5, typename t6> RaycastHitInfo(t1&& is_hit, t2&& t_value, t3&& hit_position, t4&& color, t5&& normal, t6&& hit_object) :
		is_hit(std::forward<t1>(is_hit)), 
		t_value(std::forward<t2>(t_value)), 
		hit_position(std::forward<t3>(hit_position)), 
		color(std::forward<t4>(color)), 
		normal(std::forward<t5>(normal)),
		hit_object(std::forward<t6>(hit_object)) {}
	RaycastHitInfo(const RaycastHitInfo& rhs) : is_hit(rhs.is_hit), t_value(rhs.t_value), hit_position(rhs.hit_position), color(rhs.color), normal(rhs.normal), hit_object(rhs.hit_object) {}
	RaycastHitInfo(RaycastHitInfo&& rhs) noexcept : is_hit(std::move(rhs.is_hit)), t_value(std::move(rhs.t_value)), hit_position(std::move(rhs.hit_position)), color(std::move(rhs.color)), normal(std::move(rhs.normal)), hit_object(std::move(rhs.hit_object)) {}
	inline RaycastHitInfo& operator=(const RaycastHitInfo& rhs) {
		this->is_hit = rhs.is_hit;
		this->t_value = rhs.t_value;
		this->hit_position = rhs.hit_position;
		this->color = rhs.color;
		this->normal = rhs.normal;
		this->hit_object = rhs.hit_object;
		return *this;
	}
	inline RaycastHitInfo& operator=(RaycastHitInfo&& rhs) noexcept {
		this->is_hit = std::move(rhs.is_hit);
		this->t_value = std::move(rhs.t_value);
		this->hit_position = std::move(rhs.hit_position);
		this->color = std::move(rhs.color);
		this->normal = std::move(rhs.normal);
		this->hit_object = std::move(rhs.hit_object);
		return *this;
	}

	inline bool operator==(const RaycastHitInfo& rhs) const {
		return is_hit == rhs.is_hit &&
			t_value == rhs.t_value &&
			hit_position == rhs.hit_position &&
			color == rhs.color &&
			normal == rhs.normal &&
			hit_object == rhs.hit_object;
	}
	inline bool operator!=(const RaycastHitInfo& rhs) const {
		return !(*this == rhs);
	}
	friend std::ostream& operator<<(std::ostream& os, const RaycastHitInfo& obj);
};

class CgObject {
protected:
	static const std::string str_light_source;
	static const std::string str_sphere;
	static const std::string str_plane;
	static const std::string str_triangle;
	static const std::string str_implicit_source;
	static const std::string str_type_error;

public:
	enum Type { NONE, LIGHT_SOURCE, SPHERE, PLANE, TRIANGLE, IMPLICIT_SURFACE };
	static const std::string& GetStringOf(const CgObject::Type& type) {
		switch (type) 
		{
		case LIGHT_SOURCE: return str_light_source;
		case SPHERE: return str_sphere;
		case PLANE: return str_plane;
		case TRIANGLE: return str_triangle;
		case IMPLICIT_SURFACE: return str_implicit_source;
		default: return str_type_error;
		}
	}
	static CgObject::Type GetTypeOf(const std::string& type) {
		if (type == str_light_source) return LIGHT_SOURCE;
		else if (type == str_sphere) return SPHERE;
		else if (type == str_plane) return PLANE;
		else if (type == str_triangle) return TRIANGLE;
		else if (type == str_implicit_source) return IMPLICIT_SURFACE;
		else return NONE;
	}
	
	Vector4d pos;
	Color color;
	virtual const CgObject::Type GetType() const = 0;

	template <typename t1, typename t2> CgObject(t1&& pos,t2&& color) : pos(std::forward<t1>(pos)), color(std::forward<t2>(color)) {};
	CgObject(const CgObject& rhs) : pos(rhs.pos), color(rhs.color) {};
	CgObject(CgObject&& rhs) noexcept : pos(std::move(rhs.pos)), color(std::move(rhs.color)) {};
	CgObject& operator=(const CgObject& rhs) {
		this->pos = rhs.pos;
		this->color = rhs.color;
		return *this;
	}
	CgObject& operator=(CgObject&& rhs) noexcept {
		this->pos = std::move(rhs.pos);
		this->color = std::move(rhs.color);
		return *this;
	}

	friend std::ostream& operator<<(std::ostream& os, const CgObject& obj);
};

class CgObject_HittableByRay : public CgObject {
public:
	virtual RaycastHitInfo GetRaycastHitInfo(const Ray& ray) const = 0;
	template <typename t1, typename t2> CgObject_HittableByRay(t1&& pos, t2&& color) : CgObject(std::forward<t1>(pos), std::forward<t2>(color)) {}
	CgObject_HittableByRay(const CgObject_HittableByRay& rhs) : CgObject(rhs) {}
	CgObject_HittableByRay(CgObject_HittableByRay&& rhs) noexcept : CgObject(std::move(rhs)) {}
	CgObject_HittableByRay& operator=(const CgObject_HittableByRay& rhs) {
		CgObject::operator=(rhs);
		return *this;
	}	
	CgObject_HittableByRay& operator=(CgObject_HittableByRay&& rhs) noexcept {
		CgObject::operator=(std::move(rhs));
		return *this;
	}
};

class Sphere : public CgObject_HittableByRay {
public:
	double radius;

	template <typename t1, typename t2, typename t3> Sphere(t1&& pos, t2&& color, t3&& radius) : CgObject_HittableByRay(std::forward<t1>(pos), std::forward<t2>(color)), radius(std::forward<t3>(radius)) {}
	Sphere(const Sphere& rhs) : CgObject_HittableByRay(rhs), radius(rhs.radius) {}
	Sphere(Sphere&& rhs) noexcept : CgObject_HittableByRay(std::move(rhs)), radius(std::move(rhs.radius)) {}
	Sphere& operator=(const Sphere& rhs) {
		CgObject_HittableByRay::operator=(rhs);
		this->radius = rhs.radius;
		return *this;
	}
	Sphere& operator=(Sphere&& rhs) noexcept {
		CgObject_HittableByRay::operator=(std::move(rhs));
		this->radius = std::move(rhs.radius);
		return *this;
	}

	virtual const CgObject::Type GetType() const override;
	virtual RaycastHitInfo GetRaycastHitInfo(const Ray& ray) const override;
	friend std::ostream& operator<<(std::ostream& os, const Sphere& obj);
};

class LightSource : public Sphere {
public:
	double light_strength;

	template <typename t1, typename t2, typename t3, typename t4> LightSource(t1&& pos, t2&& color, t3&& radius, t4&& light_strength) : Sphere(std::forward<t1>(pos), std::forward<t2>(color), std::forward<t3>(radius)), light_strength(std::forward<t4>(light_strength)) {}
	LightSource(const LightSource& rhs) : Sphere(rhs), light_strength(rhs.light_strength) {}
	LightSource(LightSource&& rhs) noexcept : Sphere(std::move(rhs)), light_strength(std::move(rhs.light_strength)) {}
	LightSource& operator=(const LightSource& rhs) {
		Sphere::operator=(rhs);
		this->light_strength = rhs.light_strength;
		return *this;
	}
	LightSource& operator=(LightSource&& rhs) noexcept {
		Sphere::operator=(std::move(rhs));
		this->light_strength = std::move(rhs.light_strength);
		return *this;
	}

	virtual const CgObject::Type GetType() const override;
	virtual RaycastHitInfo GetRaycastHitInfo(const Ray& ray) const {
		return Sphere::GetRaycastHitInfo(ray);
	}
	friend std::ostream& operator<<(std::ostream& os, const LightSource& obj);
};

class Plane : public CgObject_HittableByRay {

public:
	Vector4d normal;

	template <typename t1, typename t2, typename t3> Plane(t1&& pos, t2&& color, t3&& normal) : CgObject_HittableByRay(std::forward<t1>(pos), std::forward<t2>(color)), normal(std::forward<t3>(normal)) {}
	Plane(const Plane& rhs) : CgObject_HittableByRay(rhs), normal(rhs.normal) {}
	Plane(Plane&& rhs) noexcept : CgObject_HittableByRay(std::move(rhs)), normal(std::move(rhs.normal)) {}
	Plane& operator=(const Plane& rhs) {
		CgObject_HittableByRay::operator=(rhs);
		this->normal = rhs.normal;
		return *this;
	}
	Plane& operator=(Plane&& rhs) noexcept {
		CgObject_HittableByRay::operator=(std::move(rhs));
		this->normal = std::move(rhs.normal);
		return *this;
	}

	virtual const CgObject::Type GetType() const override;
	virtual RaycastHitInfo GetRaycastHitInfo(const Ray& ray) const override;
	friend std::ostream& operator<<(std::ostream& os, const Plane& obj);
};

class Triangle : public Plane {
public:
	Vector4d pos1;
	Vector4d pos2;
	Vector4d u_hat;
	Vector4d v_hat;

	template <typename t1, typename t2, typename t3, typename t4> 
	Triangle(t1&& pos, t2&& pos1, t3&& pos2, t4&& color) :
		Plane(std::forward<t1>(pos), std::forward<t4>(color), std::move((pos1 - pos) * (pos2 - pos))),
		pos1(std::forward<t2>(pos1)),
		pos2(std::forward<t3>(pos2)),
		u_hat(std::move(((pos2 - pos)* normal) / normal.dot(normal))),
		v_hat(std::move((normal* (pos1 - pos)) / normal.dot(normal))) {}
	Triangle(const Triangle& rhs) : Plane(rhs), pos1(rhs.pos1), pos2(rhs.pos2), u_hat(rhs.u_hat), v_hat(rhs.v_hat) {}
	Triangle(Triangle&& rhs) noexcept : Plane(std::move(rhs)), pos1(std::move(rhs.pos1)), pos2(std::move(rhs.pos2)), u_hat(std::move(rhs.u_hat)), v_hat(std::move(rhs.v_hat)) {}
	Triangle& operator=(const Triangle& rhs) {
		Plane::operator=(rhs);
		this->pos1 = rhs.pos1;
		this->pos2 = rhs.pos2;
		this->u_hat = rhs.u_hat;
		this->v_hat = rhs.v_hat;
		return *this;
	}
	Triangle& operator=(Triangle&& rhs) noexcept {
		Plane::operator=(std::move(rhs));
		this->pos1 = std::move(rhs.pos1);
		this->pos2 = std::move(rhs.pos2);
		this->u_hat = std::move(rhs.u_hat);
		this->v_hat = std::move(rhs.v_hat);
		return *this;
	}

	double GetU(const Vector4d& point) const;
	double GetV(const Vector4d& point) const;
	virtual const CgObject::Type GetType() const override;
	virtual RaycastHitInfo GetRaycastHitInfo(const Ray& ray) const override;
	friend std::ostream& operator<<(std::ostream& os, const Triangle& obj);
};

class ImplicitSurface : public CgObject_HittableByRay {
private:

public:
	std::vector<Vector4d> source_points;
	double t_value;

	template <typename t1, typename t2, typename t3> ImplicitSurface(t1&& color, t2&& source_points, t3&& t_value) 
		: CgObject_HittableByRay(Vector4d(), std::forward<t1>(color)), source_points(std::forward<t2>(source_points)), t_value(std::forward<t3>(t_value)) {}
	ImplicitSurface(const ImplicitSurface& rhs) : CgObject_HittableByRay(rhs), source_points(rhs.source_points), t_value(rhs.t_value) {}
	ImplicitSurface(ImplicitSurface&& rhs) noexcept : CgObject_HittableByRay(std::move(rhs)), source_points(std::move(rhs.source_points)), t_value(std::move(rhs.t_value)) {}
	ImplicitSurface& operator=(const ImplicitSurface& rhs) {
		CgObject_HittableByRay::operator=(rhs);
		this->source_points = rhs.source_points;
		this->t_value = t_value;
		return *this;
	}
	ImplicitSurface& operator=(ImplicitSurface&& rhs) noexcept {
		CgObject_HittableByRay::operator=(std::move(rhs));
		this->source_points = std::move(rhs.source_points);
		this->t_value = std::move(rhs.t_value);
		return *this;
	}

	virtual const CgObject::Type GetType() const override;
	virtual RaycastHitInfo GetRaycastHitInfo(const Ray& ray) const override;
	friend std::ostream& operator<<(std::ostream& os, const ImplicitSurface& obj);
};

#endif