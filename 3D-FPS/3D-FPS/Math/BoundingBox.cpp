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
	/*if (velocity.x < 0.0)
		min.x += velocity.x;
	if (velocity.x > 0.0)
		max.x += velocity.x;

	if (velocity.y < 0.0)
		min.y += velocity.y;
	if (velocity.y > 0.0)
		max.y += velocity.y;

	if (velocity.z < 0.0)
		min.z += velocity.z;
	if (velocity.z > 0.0)
		max.z += velocity.z;*/
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
