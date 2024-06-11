/**
* json 파일에 설정을 저장하고 읽어오기 위해 json parser 오픈소스를 사용하였음
* https://github.com/open-source-parsers/jsoncpp
*/

#include "SettingsReader.h"
#include <iostream>
#include <map>

using namespace std;

bool SettingsReader::Open(const char* filename) {
    ifstream ifs(filename, ifstream::binary);
    Json::CharReaderBuilder builder;
    Json::String errs;
    builder["collectComments"] = false;

    if (ifs.fail()) {
        cout << "'" << filename << "' 파일을 열 수 없습니다." << endl;
        return false;
    }

    if (!Json::parseFromStream(builder, ifs, &root, &errs)) {
        cout << errs << endl;
        return false;
    }

    return true;
}

void SettingsReader::ThrowIfNotOpen() const
{
    if (root.isNull()) {
        cerr << "세팅 파일이 열리지 않았습니다." << endl;
        exit(EXIT_FAILURE);
        //throw std::ios_base::failure("");
    }
}

void SettingsReader::ThrowIfInvalidFormat(bool format_check, string position) const
{
    if (!format_check) {
        cerr << "세팅 파일 형식이 잘못되었습니다: " << position << " 여부를 확인하세요.\n";
        exit(EXIT_FAILURE);
    }
}

void SettingsReader::ThrowIfNot3dVector(const Json::Value& arr, string position) const
{
    ThrowIfInvalidFormat(arr.isArray(), position + " 키가 존재하거나 배열인지");
    ThrowIfInvalidFormat(arr.size() == 3, position + " 배열 길이가 3인지");
    for (auto& i : arr) {
        ThrowIfInvalidFormat(i.isDouble(), position + string(" 배열 내 원소 형식이 실수인지"));
    }
}

void SettingsReader::ThrowIfNotColor(const Json::Value& color, string position) const
{
    if (color.isString()) {
        ThrowIfInvalidFormat(
            Color::of(color.asCString()) != Color::error,
            position + " 리터럴이 올바른지(white, black, red, green, blue 등)");
    }
    else if (color.isArray()) {
        ThrowIfNot3dVector(color, position);
        for (auto& i : color) {
            bool range_check = 0 <= i.asDouble() && i.asDouble() <= 255;
            ThrowIfInvalidFormat(range_check, position + string(" 배열 내 원소 형식이 0.0~1.0 또는 0~255 이내의 실수인지"));
        }
    }
    else {
        ThrowIfInvalidFormat(false, position + " 키 값이 올바른 리터럴이거나 배열인지");
    }
}

Vector4d SettingsReader::ToVector4d(const Json::Value& arr, const bool& is_vector = true) const {
    ThrowIfNot3dVector(arr, "3D 벡터인지");
    vector<double> v;
    for (auto& i : arr) {
        v.push_back(i.asDouble());
    }
    return Vector4d({ v[0], v[1], v[2], is_vector ? 0.0 : 1.0 });
}

Color SettingsReader::ToColor(const Json::Value& color) const
{
    ThrowIfNotColor(color, "Color인지");
    if (color.isString()) {
        return Color::of(color.asCString());
    }
    else if (color.isArray()) {
        auto vec = ToVector4d(color);
        for (int i = 0; i < 3; i++) {
            if (1 <= vec[i] && vec[i] <= 255)
                return Color(vec[0] / 255, vec[1] / 255, vec[2] / 255);
        }
        return Color(vec[0], vec[1], vec[2]);
    }
    else {
        ThrowIfNotColor(color, "Color인지");
        return Color::error;
    }
}



Vector4d SettingsReader::GetViewingParametersOf(const char* key, bool is_vector = true) const
{
    ThrowIfNotOpen();
    auto& arr = root["viewing-parameters"][key];
    ThrowIfNot3dVector(arr, string("viewing-parameters의 ") + key);
    return ToVector4d(arr, is_vector);
}

int SettingsReader::GetScreenSizeOf(int index) const
{
    ThrowIfNotOpen();
    auto& arr = root["screen-parameters"]["screen-size"];
    ThrowIfInvalidFormat(arr.isArray(), "viewing-parameters의 screen-size 키가 존재하는지");
    ThrowIfInvalidFormat(arr.size() == 2, "screen-size 배열 길이가 2인지");

    ThrowIfInvalidFormat(arr.get(Json::Value::ArrayIndex(index), Json::nullValue).isInt(), "screen-size 배열 내 원소 형식이 정수인지");
    return arr.get(Json::Value::ArrayIndex(index), Json::nullValue).asInt();
}

double SettingsReader::GetShadingParametersOf(const char* key) const
{
    ThrowIfNotOpen();
    auto& arr = root["shading-parameters"][key];
    ThrowIfInvalidFormat(arr.isDouble(), string("shading-parameters의 ") + key + " 키가 존재하는지");
    return arr.asDouble();
}



shared_ptr<CgObject> SettingsReader::SupplyCgObject(const string& type, const Json::Value& value) const
{
    const static map<CgObject::Type, function<shared_ptr<CgObject>(const Json::Value&)> > m = {
        { CgObject::Type::LIGHT_SOURCE,     [this](const Json::Value& v) { return ParseLightSource(v); }},
        { CgObject::Type::SPHERE,           [this](const Json::Value& v) { return ParseSphere(v); }},
        { CgObject::Type::PLANE,            [this](const Json::Value& v) { return ParsePlane(v); }},
        { CgObject::Type::TRIANGLE,         [this](const Json::Value& v) { return ParseTriangle(v); }},
        { CgObject::Type::IMPLICIT_SURFACE, [this](const Json::Value& v) { return ParseImplicitSurface(v); }}
    };

    if (m.find(CgObject::GetTypeOf(type)) == m.end()) {
        ThrowIfInvalidFormat(false, "objects 타입이 \"light_source\", \"sphere\", \"plane\", \"triangle\", \"implicit-surface\" 중 하나인지");
    }

    return m.find(CgObject::GetTypeOf(type))->second(value);
}

shared_ptr<LightSource> SettingsReader::ParseLightSource(const Json::Value& value) const
{
    const static string msg_prefix = "light-source 오브젝트 data에 ";
    ThrowIfNot3dVector(value["position"], msg_prefix + "position");
    ThrowIfNotColor(value["color"], msg_prefix + "color");
    ThrowIfInvalidFormat(value["radius"].isDouble(), msg_prefix + "radius 키가 있거나 실수 형식인지");
    ThrowIfInvalidFormat(value["light-strength"].isDouble(), msg_prefix + "light-strength 키가 있거나 실수 형식인지");

    return make_shared<LightSource>(
        ToVector4d(value["position"], false),
        ToColor(value["color"]),
        value["radius"].asDouble(),
        value["light-strength"].asDouble()
    );
}

shared_ptr<Sphere> SettingsReader::ParseSphere(const Json::Value& value) const
{
    const static string msg_prefix = "sphere 오브젝트 data에 ";
    ThrowIfNot3dVector(value["position"], msg_prefix + "position");
    ThrowIfNotColor(value["color"], msg_prefix + "color");
    ThrowIfInvalidFormat(value["radius"].isDouble(), msg_prefix + "radius 키가 있거나 실수 형식인지");

    return make_shared<Sphere>(
        ToVector4d(value["position"], false),
        ToColor(value["color"]),
        value["radius"].asDouble()
    );
}

shared_ptr<Plane> SettingsReader::ParsePlane(const Json::Value& value) const
{
    const static string msg_prefix = "plane 오브젝트 data에 ";
    ThrowIfNot3dVector(value["position"], msg_prefix + "position");
    ThrowIfNotColor(value["color"], msg_prefix + "color");
    ThrowIfNot3dVector(value["normal"], msg_prefix + "normal");

    return make_shared<Plane>(
        ToVector4d(value["position"], false),
        ToColor(value["color"]),
        ToVector4d(value["normal"])
    );
}

shared_ptr<Triangle> SettingsReader::ParseTriangle(const Json::Value& value) const
{
    const static string msg_prefix = "triangle 오브젝트 data에 ";
    ThrowIfInvalidFormat(value["vertices"].isArray(), "vertices 키가 있거나 배열 형식인지");
    ThrowIfNotColor(value["color"], msg_prefix + "color");

    std::vector<Vector4d> v;
    for (auto& i : value["vertices"]) {
        ThrowIfNot3dVector(i, msg_prefix + "vertices 원소");
        v.push_back(ToVector4d(i, false));
    }

    return make_shared<Triangle>(v[0], v[1], v[2], ToColor(value["color"]));
}

shared_ptr<ImplicitSurface> SettingsReader::ParseImplicitSurface(const Json::Value& value) const
{
    const static string msg_prefix = "implicit-surface 오브젝트 data";
    ThrowIfNotColor(value["color"], msg_prefix + "에 color");
    ThrowIfInvalidFormat(value["source-points"].isArray(), msg_prefix + "에 source-points 키가 있거나 배열 형식인지");
    ThrowIfInvalidFormat(value["t-value"].isDouble(), msg_prefix + "에 t-value 키가 있거나 실수 형식인지");

    vector<Vector4d> sources;

    for (const auto& source : value["source-points"]) {
        ThrowIfNot3dVector(source, msg_prefix + "의 source-points 키의 원소");
        sources.push_back(ToVector4d(source, false));
    }

    return make_shared<ImplicitSurface>(
        ToColor(value["color"]),
        std::move(sources),
        value["t-value"].asDouble()
    );
}



SettingsReader::SettingsReader(const char* filename)
{
    if (!Open(filename)) 
        exit(EXIT_FAILURE);
}

Vector4d SettingsReader::GetEyePosition() const
{
    return GetViewingParametersOf("eye-position", false);
}

Vector4d SettingsReader::GetLookAtVector() const
{
    Vector4d eye_position = GetEyePosition();
    Vector4d lookat_point = GetViewingParametersOf("lookat-point", false);
    return lookat_point - eye_position;
}

Vector4d SettingsReader::GetHeadUpVector() const
{
    return GetViewingParametersOf("headup-vector");
}



int SettingsReader::GetScreenWidth() const
{
    return GetScreenSizeOf(0);
}

int SettingsReader::GetScreenHeight() const
{
    return GetScreenSizeOf(1);
}

double SettingsReader::GetFov() const
{
    ThrowIfNotOpen();
    auto& fov = root["screen-parameters"]["fov"];
    ThrowIfInvalidFormat(fov.isDouble(), "fov 키가 존재하거나 실수인지");
    return fov.asDouble();
}



Color SettingsReader::GetBackgroundColor() const
{
    ThrowIfNotOpen();
    auto& color = root["shading-parameters"]["background-color"];
    ThrowIfNotColor(color, "shading-parameters의 background-color");
    return ToColor(color);
}

int SettingsReader::GetPhongHighlightingNFactor() const
{
    return (int)GetShadingParametersOf("phong-highlighting-n");
}

double SettingsReader::GetPhongHighlightingHFactor() const
{
    return GetShadingParametersOf("phong-highlighting-h");
}

double SettingsReader::GetAmbientFactor() const
{
    return GetShadingParametersOf("ambient-factor");
}

int SettingsReader::GetAntiAlisingFactor() const
{
    return (int)GetShadingParametersOf("anti-alising-factor");
}

std::vector<shared_ptr<CgObject>> SettingsReader::GetCgObjects() const
{
    ThrowIfNotOpen();
    auto& arr = root["objects"];
    ThrowIfInvalidFormat(arr.isArray(), "objects가 존재하는지");

    vector<shared_ptr<CgObject>> ret;

    for (const auto& obj : arr) {
        ThrowIfInvalidFormat(obj["type"].isString(), "objects 배열 내 객체 모두에 type 키가 존재하고 값 형식이 문자열인지");
        ThrowIfInvalidFormat(obj["data"].isObject(), "objects 배열 내 객체 모두에 data 키가 존재하는지");

        ret.push_back(SupplyCgObject(obj["type"].asString(), obj["data"]));
    }

    return ret;
}

