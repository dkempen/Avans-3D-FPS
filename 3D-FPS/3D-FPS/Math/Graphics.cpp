#include "Graphics.h"

Vec3f Graphics::getNormal(const Vec3f & vec1, const Vec3f & vec2, const Vec3f & vec3)
{
	const auto line1 = vec1 - vec2;
	const auto line2 = vec1 - vec3;
	auto normal = Vec3f::crossProduct(line1, line2);
	normal = normal.normalize();
	return normal;
}

void Graphics::inverseNormals(Mesh & mesh)
{
	for (auto& vertex : mesh.vertices)
	{
		vertex.fn = vertex.fn.inverse();
		vertex.vn = vertex.vn.inverse();
	}
}
