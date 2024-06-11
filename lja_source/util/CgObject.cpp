#include <cmath>
#include <map>
#include <limits>
#include "CgObject.h"
#include "CgMath.h"

const Color Color::error	= Color(-1.0, -1.0, -1.0);
const Color Color::black	= Color(0.0, 0.0, 0.0);
const Color Color::grey		= Color(0.5, 0.5, 0.5);
const Color Color::white	= Color(1.0, 1.0, 1.0);
const Color Color::red		= Color(1.0, 0.0, 0.0);
const Color Color::green	= Color(0.0, 1.0, 0.0);
const Color Color::blue		= Color(0.0, 0.0, 1.0);
const Color Color::yellow	= Color(1.0, 1.0, 0.0);
const Color Color::magenta	= Color(1.0, 0.0, 1.0);
const Color Color::cyan		= Color(0.0, 1.0, 1.0);

const std::string CgObject::str_light_source = "light-source";
const std::string CgObject::str_sphere = "sphere";
const std::string CgObject::str_plane = "plane";
const std::string CgObject::str_triangle = "triangle";
const std::string CgObject::str_implicit_source = "implicit-surface";
const std::string CgObject::str_type_error = "type-error";

const CgObject::Type LightSource::GetType() const
{
	return CgObject::Type::LIGHT_SOURCE;
}
const CgObject::Type Sphere::GetType() const
{
	return CgObject::Type::SPHERE;
}
const CgObject::Type Plane::GetType() const
{
	return CgObject::Type::PLANE;
}
const CgObject::Type Triangle::GetType() const
{
	return CgObject::Type::TRIANGLE;
}
const CgObject::Type ImplicitSurface::GetType() const {
	return CgObject::Type::IMPLICIT_SURFACE;
}

const RaycastHitInfo RaycastHitInfo::no_hit = RaycastHitInfo(false, std::numeric_limits<double>::max(), Vector4d::zero_point, Color::error, Vector4d::zero_vector, static_cast<const CgObject*>(nullptr));



Color Color::of(const char* name)
{
	const static std::map<std::string, Color> m = {
		{ "black",		Color::black },
		{ "grey",		Color::grey },
		{ "white",		Color::white },
		{ "red",		Color::red },
		{ "green",		Color::green },
		{ "blue",		Color::blue },
		{ "yellow",		Color::yellow },
		{ "magenta",	Color::magenta },
		{ "cyan",		Color::cyan }
	};

	if (m.find(name) == m.end())
		return Color::error;

	return m.find(name)->second;
}

Color operator*(double ratio, const Color& c)
{
	return c * ratio;
}

Vector4d Ray::GetPointBy(const double t_value) const
{
	return this->source + t_value * this->direction;
}

RaycastHitInfo Sphere::GetRaycastHitInfo(const Ray& ray) const
{
	const Vector4d& v = ray.direction;
	const Vector4d&& co = ray.source - this->pos;

	const double&& a = v.dot(v);
	const double&& b = v.dot(co);
	const double&& c = co.dot(co) - this->radius * this->radius;
	const double&& d = b * b - a * c;

	//no hit
	if (d <= 0 || ((-b - sqrt(d)) / a) <= 0)
		return RaycastHitInfo::no_hit;

	const double&& t = (-b - sqrt(d)) / a;
	Vector4d&& p = ray.GetPointBy(t);
	Vector4d&& normal = (p - this->pos).normalize();

	return RaycastHitInfo(true, t, std::move(p), this->color, std::move(normal), static_cast<const CgObject *>(this));
}

RaycastHitInfo Plane::GetRaycastHitInfo(const Ray& ray) const
{
	const Vector4d& o = ray.source;
	const Vector4d& v = ray.direction;
	const double& divided = v.dot(this->normal);

	//no hit
	if (CgMath::is_zero(divided) || ((this->pos - o).dot(this->normal) / divided) <= 0)
		return RaycastHitInfo::no_hit;

	const double& t = (this->pos - o).dot(this->normal) / divided;

	return RaycastHitInfo(true, t, ray.GetPointBy(t), this->color, this->normal.normalize(), static_cast<const CgObject *>(this));
}

RaycastHitInfo Triangle::GetRaycastHitInfo(const Ray& ray) const
{
	RaycastHitInfo&& info = Plane::GetRaycastHitInfo(ray);
	//no hit by plane
	if (!info.is_hit) return std::move(info);

	double u = this->GetU(info.hit_position);
	double v = this->GetV(info.hit_position);

	//no hit
	if (u <= 0 || v <= 0 || u + v >= 1)
		return RaycastHitInfo::no_hit;

	return std::move(info);
}

RaycastHitInfo ImplicitSurface::GetRaycastHitInfo(const Ray& ray) const {

	//광선과 음함수 곡면을 연립하여 얻은 t에 대한 함수
	const auto& func_im = [&](const auto& t) {
		const Vector4d& oc = ray.source - this->source_points[0];
		const double& a = ray.direction.dot(ray.direction);
		const double& b = ray.direction.dot(oc);
		const double& c = oc.dot(oc);
		auto ret = exp(-(a * t * t + 2 * b * t + c));

		for (size_t i = 1; i < this->source_points.size(); i++) {
			const Vector4d& oc = ray.source - this->source_points[i];
			const double& b = ray.direction.dot(oc);
			const double& c = oc.dot(oc);
			ret = ret + exp(-(a * t * t + 2 * b * t + c));
		}

		return ret - this->t_value;
		};

	//법선벡터를 구하기 위한 함수
	const auto& func_normal = [&](const Vector4d& p) {
		double ret = 0;
		for (size_t i = 0; i < this->source_points.size(); i++) {
			const Vector4d& pc = p - this->source_points[i];
			ret += exp(-pc.dot(pc));
		}
		return ret;
		};

	//IM으로 해를 구하고 해가 없으면 no_hit
	const std::optional<double>&& ret = CgMath::IM(func_im, { 0, 1 });
	if (!ret.has_value()) return RaycastHitInfo::no_hit;
	
	//법선벡터 구하기
	constexpr double delta = CgMath::machine_epsilon() * 1e2;
	Vector4d&& hit_pos = ray.GetPointBy(ret.value());
	Vector4d normal = Vector4d({
		func_normal({ hit_pos[0] + delta, hit_pos[1], hit_pos[2], 0 }) - func_normal({ hit_pos[0] - delta, hit_pos[1], hit_pos[2], 0 }),
		func_normal({ hit_pos[0], hit_pos[1] + delta, hit_pos[2], 0 }) - func_normal({ hit_pos[0], hit_pos[1] - delta, hit_pos[2], 0 }),
		func_normal({ hit_pos[0], hit_pos[1], hit_pos[2] + delta, 0 }) - func_normal({ hit_pos[0], hit_pos[1], hit_pos[2] - delta, 0 }),
		0 }).normalize();

	return RaycastHitInfo(true, ret.value(), std::move(hit_pos), this->color, std::move(normal), this);
}

double Triangle::GetU(const Vector4d& point) const
{
	return (point - this->pos).dot(this->u_hat);
}

double Triangle::GetV(const Vector4d& point) const
{
	return (point - this->pos).dot(this->v_hat);
}









std::ostream& operator<<(std::ostream& os, const Color& obj) {
	if (obj == Color::error)
		return os << "error";
	if (obj == Color::black)
		return os << "black";
	if (obj == Color::grey)
		return os << "grey";
	if (obj == Color::white)
		return os << "white";
	if (obj == Color::red)
		return os << "red";
	if (obj == Color::green)
		return os << "green";
	if (obj == Color::blue)
		return os << "blue";
	if (obj == Color::yellow)
		return os << "yellow";
	if (obj == Color::magenta)
		return os << "magenta";
	if (obj == Color::cyan)
		return os << "cyan";
	
	return os << "(R:" << obj.r << ", G:" << obj.g << ", B:" << obj.b << ")";
}

std::ostream& operator<<(std::ostream& os, const Ray& obj)
{
	return os << "Ray{ source:" << obj.source
		<< "; direction:" << obj.direction << " }";
}

std::ostream& operator<<(std::ostream& os, const RaycastHitInfo& obj)
{
	if (obj == RaycastHitInfo::no_hit)
		return os << "RaycastHitInfo{ is_hit:" << obj.is_hit << " }";

	return os << "RaycastHitInfo{ is_hit:" << obj.is_hit
		<< "; t_value:" << obj.t_value
		<< "; hit_position:" << obj.hit_position
		<< "; color:" << obj.color
		<< "; normal:" << obj.normal
		<< "; hit_object:" << obj.hit_object << " }";
}

std::ostream& operator<<(std::ostream& os, const CgObject& obj)
{
	std::string ignore;
	try {
		const auto& k = dynamic_cast<const LightSource&>(obj);
		return os << k;
	}
	catch (std::bad_cast& e) { ignore += e.what(); }

	try {
		const auto& k = dynamic_cast<const Sphere&>(obj);
		return os << k;
	}
	catch (std::bad_cast& e) { ignore += e.what(); }

	try {
		const auto& k = dynamic_cast<const Triangle&>(obj);
		return os << k;
	}
	catch (std::bad_cast& e) { ignore += e.what(); }

	try {
		const auto& k = dynamic_cast<const Plane&>(obj);
		return os << k;
	}
	catch (std::bad_cast& e) { ignore += e.what(); }

	try {
		const auto& k = dynamic_cast<const ImplicitSurface&>(obj);
		return os << k;
	}
	catch (std::bad_cast& e) { ignore += e.what(); }

	std::cerr << "dynamic_cast가 실패하였음" << std::endl;
	exit(EXIT_FAILURE);
	return os;
}

std::ostream& operator<<(std::ostream& os, const LightSource& obj)
{
	return os << "LightSource{ pos:" << obj.pos 
		<< "; color:" << obj.color 
		<< "; radius:" << obj.radius 
		<< "; light_strength:" << obj.light_strength << " }";
}

std::ostream& operator<<(std::ostream& os, const Sphere& obj)
{
	return os << "Sphere{ pos:" << obj.pos
		<< "; color:" << obj.color
		<< "; radius:" << obj.radius << " }";
}

std::ostream& operator<<(std::ostream& os, const Plane& obj)
{
	return os << "Plane{ pos:" << obj.pos
		<< "; color:" << obj.color
		<< "; normal:" << obj.normal << " }";
}

std::ostream& operator<<(std::ostream& os, const Triangle& obj)
{
	return os << "Triangle{ pos:" << obj.pos
		<< "; pos1:" << obj.pos1
		<< "; pos2:" << obj.pos2
		<< "; color:" << obj.color << " }";
}

std::ostream& operator<<(std::ostream& os, const ImplicitSurface& obj) {
	os << "ImplicitSurface{ color:" << obj.color << "; source-points: [ ";
	for (const auto& e : obj.source_points) os << e << "; ";
	return os << "]; t-value: " << obj.t_value << " }";
}