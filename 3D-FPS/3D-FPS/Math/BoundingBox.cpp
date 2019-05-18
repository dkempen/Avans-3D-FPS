#include "BoundingBox.h"

BoundingBox::BoundingBox()
{
	min = { 0, 0, 0 };
	max = { 0, 0, 0 };
} 

BoundingBox::BoundingBox(const BoundingBox& boundingBox)
{
	min = boundingBox.min;
	max = boundingBox.max;
}

BoundingBox::BoundingBox(Vec3f min, Vec3f max)
{
	this->min = min;
	this->max = max;
}

BoundingBox BoundingBox::getAbsoluteBox(const Vec3f position) const
{
	BoundingBox absolute(*this);
	absolute.min = {
		position.x + min.x,
		position.y + min.y,
		position.z + min.z };
	absolute.max = {
		position.x + max.x,
		position.y + max.y,
		position.z + max.z };
	return absolute;
}
