#pragma once
#include "../Math/Graphics.h"

class ObjLoader {
public:
	/*
		Loads the obj file and extracts the vertices which form the mesh

		@param filename - The name of the file

		Returns the extracted mesh
	*/
	static Graphics::Mesh loadObj(std::string filename);

private:
	/*
	Adds a triangle to the given mesh

	@param mesh           - The given mesh
	@param verts          - The vertices
	@param texture_coords - The texture coordinates
	@param normals        - The normals
	@param index		  - The index of the vertex
	@param verticesdata   - The values of all the vertices, texture coordinates and normals
	*/
	static void addTriangle(Graphics::Mesh &mesh,
		const std::vector<Vec3f> &verts,
		const std::vector<Vec2f> &texture_coords,
		const std::vector<Vec3f> &normals,
		int index,
		const std::vector<std::vector<std::string>> &verticesdata);
};
