#pragma once
#ifndef __RAYCASTER_H__
#define __RAYCASTER_H__
#include <cmath>
#include <vector>
#include <memory>
#include "CgObject.h"
#include "CgMath.h"
#include "SettingsReader.h"

using namespace std;

class ScreenParameter {
private:

public:
	int width;
	int height;
	double fov;
	double distance;

	int left;
	int right;
	int bottom;
	int top;

	ScreenParameter(int width, int height, double fov) :
		width(width), height(height), 
		fov(fov), distance(height / (2 * tan(CgMath::DegToRad(fov / 2)))),
		left(-width / 2), right(width / 2),
		bottom(-height / 2), top(height / 2) {}

	ScreenParameter() : ScreenParameter(0, 0, 0) {}
};

class ViewingParameter {
public:
	Vector4d eye_position;
	Vector4d lookat_vector;
	Vector4d headup_vector;

	Vector4d eye_u;
	Vector4d eye_v;
	Vector4d eye_w;
	Matrix4d M;

	template <typename t1, typename t2, typename t3> ViewingParameter(t1&& eye_position, t2&& lookat_vector, t3&& headup_vector) :
		eye_position(std::forward<t1>(eye_position)), 
		lookat_vector(std::forward<t2>(lookat_vector)), 
		headup_vector(std::forward<t3>(headup_vector)),
		eye_u((this->lookat_vector * this->headup_vector).normalize()),
		eye_v((eye_u * this->lookat_vector).normalize()),
		eye_w(-this->lookat_vector.normalize()),
		M(Matrix4d(eye_u, eye_v, eye_w, this->eye_position)) {  }
	ViewingParameter() {}
	ViewingParameter(const ViewingParameter& rhs) :
		eye_position(rhs.eye_position), lookat_vector(rhs.lookat_vector), headup_vector(rhs.headup_vector),
		eye_u(rhs.eye_u), eye_v(rhs.eye_v), eye_w(rhs.eye_w), M(rhs.M) {}
	ViewingParameter(ViewingParameter&& rhs) noexcept :
		eye_position(rhs.eye_position), lookat_vector(rhs.lookat_vector), headup_vector(rhs.headup_vector),
		eye_u(rhs.eye_u), eye_v(rhs.eye_v), eye_w(rhs.eye_w), M(rhs.M) {}
	ViewingParameter& operator=(const ViewingParameter& rhs) {
		this->eye_position = rhs.eye_position;
		this->lookat_vector = rhs.lookat_vector;
		this->headup_vector = rhs.headup_vector;
		this->eye_u = rhs.eye_u;
		this->eye_v = rhs.eye_v;
		this->eye_w = rhs.eye_w;
		this->M = rhs.M;
		return *this;
	}	
	ViewingParameter& operator=(ViewingParameter&& rhs) noexcept {
		this->eye_position = std::move(rhs.eye_position);
		this->lookat_vector = std::move(rhs.lookat_vector);
		this->headup_vector = std::move(rhs.headup_vector);
		this->eye_u = std::move(rhs.eye_u);
		this->eye_v = std::move(rhs.eye_v);
		this->eye_w = std::move(rhs.eye_w);
		this->M = std::move(rhs.M);
		return *this;
	}
};

class ShadingParameter {
public:
	Color background;
	int phong_highlighting_n;
	double phong_highlighting_h;
	double ambient;
	int anti_alising_level;

	template <typename t1, typename t2, typename t3, typename t4, typename t5> ShadingParameter(t1&& background, t2&& phong_highlighting_n, t3&& phong_highlighting_h, t4&& ambient, t5&& anti_alising_level) :
		background(std::forward<t1>(background)),
		phong_highlighting_n(std::forward<t2>(phong_highlighting_n)),
		phong_highlighting_h(std::forward<t3>(phong_highlighting_h)),
		ambient(std::forward<t4>(ambient)),
		anti_alising_level(std::forward<t5>(anti_alising_level)) {}
	ShadingParameter() : ShadingParameter(Color::black, 0, 0, 0, 0) {}
	ShadingParameter(const ShadingParameter& rhs) :
		background(rhs.background),
		phong_highlighting_n(rhs.phong_highlighting_n),
		phong_highlighting_h(rhs.phong_highlighting_h),
		ambient(rhs.ambient),
		anti_alising_level(rhs.anti_alising_level) {}
	ShadingParameter(ShadingParameter&& rhs) noexcept :
		background(std::move(rhs.background)),
		phong_highlighting_n(std::move(rhs.phong_highlighting_n)),
		phong_highlighting_h(std::move(rhs.phong_highlighting_h)),
		ambient(std::move(rhs.ambient)),
		anti_alising_level(std::move(rhs.anti_alising_level)) {}
	ShadingParameter& operator=(const ShadingParameter& rhs) {
		this->background = rhs.background;
		this->phong_highlighting_n = rhs.phong_highlighting_n;
		this->phong_highlighting_h = rhs.phong_highlighting_h;
		this->ambient = rhs.ambient;
		this->anti_alising_level = rhs.anti_alising_level;
		return *this;
	}
	ShadingParameter& operator=(ShadingParameter&& rhs) noexcept {
		this->background = std::move(rhs.background);
		this->phong_highlighting_n = std::move(rhs.phong_highlighting_n);
		this->phong_highlighting_h = std::move(rhs.phong_highlighting_h);
		this->ambient = std::move(rhs.ambient);
		this->anti_alising_level = std::move(rhs.anti_alising_level);
		return *this;
	}
};

class ScreenToWorldRaycaster {
private:
	ScreenParameter screen;
	ViewingParameter viewing;
	ShadingParameter shading;

	vector<shared_ptr<LightSource>> light;
	vector<shared_ptr<CgObject_HittableByRay>> hittable;

	void PrintAcceptedSettings() const;
	void InitCgObjects(const vector<shared_ptr<CgObject>>& object);
	RaycastHitInfo GetFirstHitInfo(const Ray& ray) const;
	inline Ray GetEyeToPixelRay(const double& screen_x, const double& screen_y) const;
	inline Vector4d GetLightDirection(const Vector4d& hit_position) const;
	inline Ray GetLightRay(const Vector4d& hit_position) const;
	inline bool InShadow(const RaycastHitInfo& light_hit) const;
	inline double GetLightIntensity(const LightSource& light, const Ray& to_light) const;
	inline double GetLambertCosValue(const Vector4d& light_direction, const Vector4d& normal, const double& ambient) const;
	inline Vector4d Reflected(const Vector4d& normal, const Vector4d& incident) const;
	inline Color PhongHighlightColor(int n, double h, const LightSource& light, const double& light_intensity, const RaycastHitInfo& info, const Ray& ray, const Vector4d& eye_position, const Color& color) const;
	inline Color GetColorOf(const double& screen_x, const double& screen_y) const;
	inline Color GetAntiAlisedColorOf(const double& screen_x, const double& screen_y) const;

public:
	ScreenToWorldRaycaster(const SettingsReader& config);
	Color GetColor(int screen_x, int screen_y) const;
	void NotifyScreenSizeChanged(int new_screen_width, int new_screen_height);
	const ScreenParameter& GetScreenParameter() const { return screen; }
};

#endif