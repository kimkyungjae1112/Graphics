#include "Raycaster.h"
#include "CgObject.h"
#include <iostream>



RaycastHitInfo ScreenToWorldRaycaster::GetFirstHitInfo(const Ray& ray) const
{
	RaycastHitInfo&& ret = RaycastHitInfo(RaycastHitInfo::no_hit);

	for (const auto& obj : hittable) {
		RaycastHitInfo&& info = obj->GetRaycastHitInfo(ray);

		if (!info.is_hit) continue;
		if (info.t_value < 1e-9) continue;
		if (info.t_value >= ret.t_value) continue;

		ret = std::move(info);
	}

	return std::move(ret);
}

inline Ray ScreenToWorldRaycaster::GetEyeToPixelRay(const double& screen_x, const double& screen_y) const
{
	Vector4d&& pixel_position = viewing.M * Vector4d({ screen_x, screen_y, -screen.distance, 1.0 });
	return Ray(viewing.eye_position, std::move(pixel_position) - viewing.eye_position);
}



inline Vector4d ScreenToWorldRaycaster::GetLightDirection(const Vector4d& hit_position) const
{
	return light[0]->pos - hit_position;
}

inline Ray ScreenToWorldRaycaster::GetLightRay(const Vector4d& hit_position) const
{
	return Ray(hit_position, GetLightDirection(hit_position));
}

inline bool ScreenToWorldRaycaster::InShadow(const RaycastHitInfo& light_hit) const
{
	const double& t = light_hit.t_value;
	return light_hit.is_hit && 1e-9 <= t && t <= 1 && light_hit.hit_object->GetType() != CgObject::Type::LIGHT_SOURCE;
}

inline double ScreenToWorldRaycaster::GetLightIntensity(const LightSource& light, const Ray& to_light) const
{
	return 1.0 / pow(to_light.direction.norm() / light.light_strength, 2);
}

inline double ScreenToWorldRaycaster::GetLambertCosValue(const Vector4d& light_direction, const Vector4d& normal, const double& ambient) const
{
	return CgMath::LinearInterpolation(-1, 1, light_direction.cos(normal), ambient, 1);
}

inline Vector4d ScreenToWorldRaycaster::Reflected(const Vector4d& normal, const Vector4d& incident) const
{
	return incident - 2 * normal * (incident.dot(normal) / normal.dot(normal));
}

inline Color ScreenToWorldRaycaster::PhongHighlightColor(int n, double h, const LightSource& light, const double& light_intensity, const RaycastHitInfo& info, const Ray& ray, const Vector4d& eye_position, const Color& color) const
{
	double&& factor = pow(Reflected(info.normal, ray.direction).cos(info.hit_position - eye_position), n);
	
	if (factor >= h) {
		const Color&& new_max = CgMath::LinearInterpolation(Color::black, Color::white, Color::white * light_intensity, color, Color::white);
		return CgMath::LinearInterpolation(Color::white * h, Color::white, Color::white * factor, color, new_max);
	}
	return color;
}



ScreenToWorldRaycaster::ScreenToWorldRaycaster(const SettingsReader& config) {
	screen = ScreenParameter(
		config.GetScreenWidth(),
		config.GetScreenHeight(),
		config.GetFov());

	viewing = ViewingParameter(
		config.GetEyePosition(),
		config.GetLookAtVector(),
		config.GetHeadUpVector());

	shading = ShadingParameter(
		config.GetBackgroundColor(),
		config.GetPhongHighlightingNFactor(),
		config.GetPhongHighlightingHFactor(),
		config.GetAmbientFactor(),
		config.GetAntiAlisingFactor()
	);

	InitCgObjects(config.GetCgObjects());
	PrintAcceptedSettings();
}

void ScreenToWorldRaycaster::PrintAcceptedSettings() const
{
	printf("==========================   Current Settings   =========================\n");
	printf("\t<== Screen Parameters ==>\n");
	printf("Screen Size(w*h): %dx%d\n", screen.width, screen.height);
	printf("Screen Left: %d; Right: %d; Top: %d; Bottom: %d\n", screen.left, screen.right, screen.top, screen.bottom);
	printf("FOV: %.2lf; Distance: %.2lf\n\n", screen.fov, screen.distance);
	
	printf("\t<== Viewing Parameters ==>\n"); 
	cout << "Eye Position: " << viewing.eye_position << endl;
	cout << "Look At Vector: " << viewing.lookat_vector << endl;
	cout << "Head Up Vector: " << viewing.headup_vector << endl;
	cout << "u_hat: " << viewing.eye_u << endl;
	cout << "v_hat: " << viewing.eye_v << endl;
	cout << "w_hat: " << viewing.eye_w << endl;
	cout << "Matrix M:\n" << viewing.M << endl;

	printf("\t<== Shading Parameters ==>\n"); 
	cout << "Background Color: " << shading.background << endl;
	printf("Phong Highlighting factors: (N=%d, H=%.2f)\n", shading.phong_highlighting_n, shading.phong_highlighting_h);
	printf("Ambient Factor: %.2f; Anti-Alising Factor: %d\n\n", shading.ambient, shading.anti_alising_level);

	printf("\t<== CG Objects ==>\n"); 
	printf("Total CgObject Count: %d, Lights: %d, Hittable Objects: %d\n", light.size() + hittable.size(), light.size(), hittable.size());
	printf("Lights:\n");
	for (const auto& e : light) cout << *e << endl;	
	printf("Hittable Objects:\n");
	for (const auto& e : hittable) cout << *e << endl;
	printf("=========================================================================\n");
}

void ScreenToWorldRaycaster::InitCgObjects(const vector<shared_ptr<CgObject>>& object)
{
	static bool is_init = false;
	if (is_init) {
		return;
	}

	for (const auto& obj : object) {
		const auto& obj_light = dynamic_pointer_cast<LightSource>(obj);
		if (obj_light != nullptr) {
			light.push_back(obj_light);
			//continue;
		}

		const auto& obj_hittable = dynamic_pointer_cast<CgObject_HittableByRay>(obj);
		if (obj_hittable != nullptr) {
			hittable.push_back(obj_hittable);
			continue;
		}

		cout << "CG 오브젝트의 RTTI가 실패하였음\n";
		exit(EXIT_FAILURE);
	}

	is_init = true;
}



Color ScreenToWorldRaycaster::GetColorOf(const double& screen_x, const double& screen_y) const
{
	RaycastHitInfo&& info = GetFirstHitInfo(GetEyeToPixelRay(screen_x, screen_y));
	if (!info.is_hit) return shading.background;

	Ray&& ray = GetLightRay(info.hit_position);
	Color& c = info.color;
	if (InShadow(GetFirstHitInfo(ray))) return c * shading.ambient;

	const double&& intensity = GetLightIntensity(*light[0], ray);
	const double& ratio = max(shading.ambient, intensity * GetLambertCosValue(ray.direction, info.normal, shading.ambient));
	c = ratio * c;
	c = PhongHighlightColor(shading.phong_highlighting_n, shading.phong_highlighting_h, *light[0], intensity, info, ray, viewing.eye_position, c);

	return c;
}

inline Color ScreenToWorldRaycaster::GetAntiAlisedColorOf(const double& screen_x, const double& screen_y) const
{
	int anti_level = shading.anti_alising_level;
	double r = 0, g = 0, b = 0;

	for (int y = 0; y < anti_level; y++) {
		for (int x = 0; x < anti_level; x++) {
			Color&& result = GetColorOf(screen_x + double(x) / anti_level, screen_y + double(y) / anti_level);
			r += result.r;
			g += result.g;
			b += result.b;
		}
	}
	anti_level *= anti_level;
	return Color(r / anti_level, g / anti_level, b / anti_level);
}

Color ScreenToWorldRaycaster::GetColor(int screen_x, int screen_y) const {
	return GetAntiAlisedColorOf(double(screen_x), double(screen_y));
}

void ScreenToWorldRaycaster::NotifyScreenSizeChanged(int new_screen_width, int new_screen_height)
{
	screen = ScreenParameter(new_screen_width, new_screen_height, screen.fov);
}
