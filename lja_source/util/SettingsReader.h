/**
* json 파일에 설정을 저장하고 읽어오기 위해 json parser 오픈소스를 사용하였음
* https://github.com/open-source-parsers/jsoncpp
*/

#pragma once
#ifndef __SETTINGS_READER_H__
#define __SETTINGS_READER_H__

#include <fstream>
#include <vector>
#include <memory>
#include <functional>
#include "json/json.h"
#include "MyMatrix.h"
#include "CgObject.h"

using namespace jangan_lee_my_matrix;
using namespace std;

class SettingsReader {
private:
    Json::Value root;

    //filename으로부터 json을 불러옴
    bool Open(const char* filename);
    void ThrowIfNotOpen() const;
    void ThrowIfInvalidFormat(bool format_check, string position) const;
    void ThrowIfNot3dVector(const Json::Value& array, string position) const;
    Vector4d ToVector4d(const Json::Value& arr, const bool& is_vector) const;
    void ThrowIfNotColor(const Json::Value& color, string position) const;
    Color ToColor(const Json::Value& color) const;

    Vector4d GetViewingParametersOf(const char* key, bool is_vector) const;
    int GetScreenSizeOf(int index) const;
    double GetShadingParametersOf(const char* key) const;
    shared_ptr<CgObject> SupplyCgObject(const string& type, const Json::Value& value) const;
    shared_ptr<LightSource> ParseLightSource(const Json::Value& value) const;
    shared_ptr<Sphere> ParseSphere(const Json::Value& value) const;
    shared_ptr<Plane> ParsePlane(const Json::Value& value) const;
    shared_ptr<Triangle> ParseTriangle(const Json::Value& value) const;
    shared_ptr<ImplicitSurface> ParseImplicitSurface(const Json::Value& value) const;

public:
    SettingsReader(const char* filename);

    Vector4d GetEyePosition() const;
    Vector4d GetLookAtVector() const;
    Vector4d GetHeadUpVector() const;

    int GetScreenWidth() const;
    int GetScreenHeight() const;
    double GetFov() const;

    Color GetBackgroundColor() const;
    int GetPhongHighlightingNFactor() const;
    double GetPhongHighlightingHFactor() const;
    double GetAmbientFactor() const;
    int GetAntiAlisingFactor() const;

    vector<shared_ptr<CgObject>> GetCgObjects() const;
};

#endif