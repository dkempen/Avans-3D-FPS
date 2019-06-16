#pragma once

#include <vector>
#include "Vec.h"

class Graphics
{
public:
	struct Vertex
	{
		// Vertex position
		Vec3f p;
		// Vertex normal
		Vec3f vn;
		// Texture coordinate
		Vec2f vt;
		// Face normal
		Vec3f fn;
	};

	struct Mesh
	{
		std::vector<Vertex> vertices;
	};

	/*
		Calculates the normal of the given three vertices (triangle)

		@param vec1 - The first vertex
		@param vec2 - The second vertex
		@param vec3 - The third vertex

		Returns the resulting normal
	*/
	static Vec3f getNormal(const Vec3f &vec1, const Vec3f &vec2, const Vec3f &vec3);

	/*
		Inverses all the normals in the mesh

		@param mesh - The given mesh
	*/
	static void inverseNormals(Mesh &mesh);
};
