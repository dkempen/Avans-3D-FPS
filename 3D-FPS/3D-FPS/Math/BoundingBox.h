#pragma once
#include "Vec.h"

class BoundingBox
{
public:
	Vec3f min;
	Vec3f max;

	BoundingBox();
	BoundingBox(const BoundingBox &boundingBox);
	BoundingBox(Vec3f min, Vec3f max);
	~BoundingBox() = default;

	BoundingBox getAbsoluteBox(Vec3f position) const;
};
