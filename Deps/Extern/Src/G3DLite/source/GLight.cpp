/**
  @file GLight.cpp

  @maintainer Morgan McGuire, http://graphics.cs.williams.edu

  @created 2003-11-12
  @edited  2009-11-16
*/
#include "G3D/GLight.h"
#include "G3D/Sphere.h"
#include "G3D/CoordinateFrame.h"
#include "G3D/Any.h"
#include "G3D/stringutils.h"
#include "G3D/units.h"

namespace G3D {

GLight::GLight(const Any& any) {
    any.verifyNameBeginsWith("GLight");

    if (any.type() == Any::TABLE) {
        *this = GLight();
        Vector3 spotTarget;
        bool hasSpotTarget = false;
        for (Any::AnyTable::Iterator it = any.table().begin(); it.hasMore(); ++it) {
            const std::string& key = it->key;
            if (key == "position") {
                position = it->value;
            } else if (key == "rightDirection") {
                rightDirection = it->value;
            } else if (key == "spotDirection") {
                spotDirection = Vector3(it->value).directionOrZero();
            } else if (key == "spotTarget") {
                spotTarget = it->value;
                hasSpotTarget = true;
            } else if (key == "spotHalfAngle") {
                spotHalfAngle = it->value.number();
            } else if (key == "spotSquare") {
                spotSquare = it->value.boolean();
            } else if (key == "attenuation") {
                attenuation[0] = it->value[0].number();
                attenuation[1] = it->value[1].number();
                attenuation[2] = it->value[2].number();
            } else if (key == "color") {
                color = it->value;
            } else if (key == "enabled") {
                enabled = it->value.boolean();
            } else if (key == "castsShadows") {
                castsShadows = it->value.boolean();
            } else {
                any.verify(false, "Illegal key: " + key);
            }
        }
        if (hasSpotTarget) {
            spotDirection = (spotTarget - position.xyz()).direction();
        }
    } else if (any.name() == "GLight::directional") {

        *this = directional(Vector3(any[0]), Color3(any[1]), 
                            (any.size() > 2) ? any[2] : Any(true));

    } else if (any.name() == "GLight::point") {

        *this = point(Point3(any[0]), Power3(any[1]), 
                      (any.size() > 2) ? any[2] : Any(0.01f), 
                      (any.size() > 3) ? any[3] : Any(0), 
                      (any.size() > 4) ? any[4] : Any(1.0f), 
                      (any.size() > 5) ? any[5] : Any(true));

    } else if (any.name() == "GLight::spot") {

        *this = spot(Point3(any[0]), Vector3(any[1]), any[2], Color3(any[3]),
                     (any.size() > 4) ? any[4] : Any(0.01f),
                     (any.size() > 5) ? any[5] : Any(0.0f), 
                     (any.size() > 6) ? any[6] : Any(1.0f), 
                     (any.size() > 7) ? any[7] : Any(true));

    } else if (any.name() == "GLight::spotTarget") {

        *this = spotTarget(Point3(any[0]), Vector3(any[1]), any[2], Color3(any[3]),
                     (any.size() > 4) ? any[4] : Any(0.01f),
                     (any.size() > 5) ? any[5] : Any(0.0f), 
                     (any.size() > 6) ? any[6] : Any(1.0f), 
                     (any.size() > 7) ? any[7] : Any(true));
    } else {
        any.verify(false, "Unrecognized name");
    }
}


Any GLight::toAny() const {
    Any a(Any::TABLE, "GLight");
    a["position"]       = position;
    a["rightDirection"] = rightDirection;;
    a["spotDirection"]  = spotDirection;;
    a["spotHalfAngle"]  = spotHalfAngle;
    a["spotSquare"]     = spotSquare;

    Any att(Any::ARRAY);
    att.append(Any(attenuation[0]), Any(attenuation[1]), Any(attenuation[2]));
    a["attenuation"]  = att;
    a["color"]        = color;
    a["enabled"]      = enabled;
    a["castsShadows"] = castsShadows;

    return a;
}

    
Power3 GLight::power() const {
    if (spotHalfAngle >= pif()) {
        return color;
    } else {
        return 0.5f *  (1.0f - cosf(spotHalfAngle)) * color;
    }
}


GLight::GLight() :
    position(0, 0, 0, 0),
    rightDirection(0,0,0),
    spotDirection(0, 0, -1),
    spotHalfAngle(pif()),
    spotSquare(false),
    color(Color3::white()),
    enabled(false),
    castsShadows(true) {

    attenuation[0]  = 0.0001f;
    attenuation[1]  = 0.0f;
    attenuation[2]  = 1.0f;
}


GLight GLight::directional(const Vector3& toLight, const Color3& color, bool s) {
    GLight L;
    L.position = Vector4(toLight.direction(), 0);
    L.color    = color;
    L.castsShadows = s;
    return L;
}


GLight GLight::point(const Vector3& pos, const Color3& color, float constAtt, float linAtt, float quadAtt, bool s) {
    GLight L;
    L.position = Vector4(pos, 1);
    L.color    = color;
    L.attenuation[0] = constAtt;
    L.attenuation[1] = linAtt;
    L.attenuation[2] = quadAtt;
    L.castsShadows   = s;
    return L;
}


GLight GLight::spot(const Vector3& pos, const Vector3& pointDirection, float spotHalfAngle, const Color3& color, float constAtt, float linAtt, float quadAtt, bool s) {
    GLight L;
    L.position       = Vector4(pos, 1.0f);
    L.spotDirection  = pointDirection.direction();
    debugAssert(spotHalfAngle <= pif() / 2.0f);
    L.spotHalfAngle     = spotHalfAngle;
    L.color          = color;
    L.attenuation[0] = constAtt;
    L.attenuation[1] = linAtt;
    L.attenuation[2] = quadAtt;
    L.castsShadows   = s;
    return L;
}


bool GLight::operator==(const GLight& other) const {
    return (position == other.position) && 
        (rightDirection == other.rightDirection) &&
        (spotDirection == other.spotDirection) &&
        (spotHalfAngle == other.spotHalfAngle) &&
        (spotSquare == other.spotSquare) &&
        (attenuation[0] == other.attenuation[0]) &&
        (attenuation[1] == other.attenuation[1]) &&
        (attenuation[2] == other.attenuation[2]) &&
        (color == other.color) &&
        (enabled == other.enabled) &&
        (castsShadows == other.castsShadows);
}


bool GLight::operator!=(const GLight& other) const {
    return !(*this == other);
}


Sphere GLight::effectSphere(float cutoff) const {
    if (position.w == 0) {
        // Directional light
        return Sphere(Vector3::zero(), finf());
    } else {
        // Avoid divide by zero
        cutoff = max(cutoff, 0.00001f);
        float maxIntensity = max(color.r, max(color.g, color.b));

        float radius = finf();
            
        if (attenuation[2] != 0) {

            // Solve I / attenuation.dot(1, r, r^2) < cutoff for r
            //
            //  a[0] + a[1] r + a[2] r^2 > I/cutoff
            //
            
            float a = attenuation[2];
            float b = attenuation[1];
            float c = attenuation[0] - maxIntensity / cutoff;
            
            float discrim = square(b) - 4 * a * c;
            
            if (discrim >= 0) {
                discrim = sqrt(discrim);
                
                float r1 = (-b + discrim) / (2 * a);
                float r2 = (-b - discrim) / (2 * a);

                if (r1 < 0) {
                    if (r2 > 0) {
                        radius = r2;
                    }
                } else if (r2 > 0) {
                    radius = min(r1, r2);
                } else {
                    radius = r1;
                }
            }
                
        } else if (attenuation[1] != 0) {
            
            // Solve I / attenuation.dot(1, r) < cutoff for r
            //
            // r * a[1] + a[0] = I / cutoff
            // r = (I / cutoff - a[0]) / a[1]

            float radius = (maxIntensity / cutoff - attenuation[0]) / attenuation[1];
            radius = max(radius, 0.0f);
        }

        return Sphere(position.xyz(), radius);

    }
}


CoordinateFrame GLight::frame() const {
    CoordinateFrame f;
    if (rightDirection == Vector3::zero()) {
        // No specified right direction; choose one automatically
        if (position.w == 0) {
            // Directional light
            f.lookAt(-position.xyz());
        } else {
            // Spot light
            f.lookAt(spotDirection);
        }
    } else {
        const Vector3& Z = -spotDirection.direction();
        Vector3 X = rightDirection.direction();

        // Ensure the vectors are not too close together
        while (abs(X.dot(Z)) > 0.9f) {
            X = Vector3::random();
        }

        // Ensure perpendicular
        X -= Z * Z.dot(X);
        const Vector3& Y = Z.cross(X);

        f.rotation.setColumn(Vector3::X_AXIS, X);
        f.rotation.setColumn(Vector3::Y_AXIS, Y);
        f.rotation.setColumn(Vector3::Z_AXIS, Z);
    }
    f.translation = position.xyz();

    return f;
}


} // G3D
