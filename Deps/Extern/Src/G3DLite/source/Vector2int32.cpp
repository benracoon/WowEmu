/**
 @file Vector2int32.cpp
 
 @author Morgan McGuire, http://graphics.cs.williams.edu
  
 @created 2003-08-09
 @edited  2010-01-29
 */

#include "G3D/platform.h"
#include "G3D/g3dmath.h"
#include "G3D/Vector2int32.h"
#include "G3D/Vector2.h"
#include "G3D/BinaryInput.h"
#include "G3D/BinaryOutput.h"
#include "G3D/Vector2int16.h"

namespace G3D {
Vector2int32::Vector2int32(const class Vector2int16& v) : x(v.x), y(v.y) {
}

Vector2int32::Vector2int32(const class Vector2& v) {
    x = (int32)iFloor(v.x + 0.5);
    y = (int32)iFloor(v.y + 0.5);
}


Vector2int32::Vector2int32(class BinaryInput& bi) {
    deserialize(bi);
}


void Vector2int32::serialize(class BinaryOutput& bo) const {
    bo.writeInt32(x);
    bo.writeInt32(y);
}


void Vector2int32::deserialize(class BinaryInput& bi) {
    x = bi.readInt32();
    y = bi.readInt32();
}


Vector2int32 Vector2int32::clamp(const Vector2int32& lo, const Vector2int32& hi) {
    return Vector2int32(iClamp(x, lo.x, hi.x), iClamp(y, lo.y, hi.y));
}


}
