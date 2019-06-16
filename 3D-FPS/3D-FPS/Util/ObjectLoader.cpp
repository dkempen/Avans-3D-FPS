#include "ObjectLoader.h"
#include <fstream>
#include <strstream>
#include <sstream>
#include <string>

static std::vector<std::string> split(std::string str, const char separator)
{
	std::vector<std::string> strings;
	std::istringstream f(str);
	std::string s;

	while (std::getline(f, s, separator))
		strings.push_back(s);

	return strings;
}

Graphics::Mesh ObjLoader::loadObj(std::string filename)
{
	Graphics::Mesh mesh;

	std::ifstream f(filename);
	if (!f.is_open())
		return mesh;

	std::vector<Vec3f> verts;
	std::vector<Vec2f> texture_coords;
	std::vector<Vec3f> normals;

	while (!f.eof())
	{
		std::string line;
		std::getline(f, line);
		std::strstream s;
		s << line;

		char junk;

		//Vertex
		if (line[0] == 'v' && line[1] == ' ')
		{
			Vec3f v;
			s >> junk >> v.x >> v.y >> v.z;
			verts.push_back(v);
		}
		//Texture
		else if (line[0] == 'v' && line[1] == 't')
		{
			Vec2f vt;
			s >> junk >> junk >> vt.x >> vt.y;
			texture_coords.push_back(vt);
		}
		//Normal
		else if (line[0] == 'v' && line[1] == 'n')
		{
			Vec3f vn;
			s >> junk >> junk >> vn.x >> vn.y >> vn.z;
			normals.push_back(vn);
		}
		//Polygon
		else if (line[0] == 'f')
		{
			std::string remaining = line;
			remaining = remaining.substr(2, remaining.size());
			std::vector<std::string> indices = split(remaining, ' ');

			std::vector<std::vector<std::string>> verticesdata;
			for (int i = 0; i < indices.size(); i++) {
				std::vector<std::string> vertexdata = split(indices[i], '/');

				verticesdata.push_back(vertexdata);

				if (i >= 2) {
					addTriangle(mesh, verts, texture_coords, normals, i, verticesdata);
				}
			}
		}
	}

	return mesh;
}

void ObjLoader::addTriangle(Graphics::Mesh &mesh,
	const std::vector<Vec3f> &verts,
	const std::vector<Vec2f> &texture_coords,
	const std::vector<Vec3f> &normals,
	const int index,
	const std::vector<std::vector<std::string>> &verticesdata) {
	Graphics::Vertex vert;
	Graphics::Vertex vert2;
	Graphics::Vertex vert3;

	if (!texture_coords.empty())
	{
		vert.vt = texture_coords[atoi(verticesdata[0][1].c_str()) - 1];
		vert2.vt = texture_coords[atoi(verticesdata[index - 1][1].c_str()) - 1];
		vert3.vt = texture_coords[atoi(verticesdata[index][1].c_str()) - 1];
	}
	if (!normals.empty())
	{
		vert.vn = normals[atoi(verticesdata[0][2].c_str()) - 1];
		vert2.vn = normals[atoi(verticesdata[index - 1][2].c_str()) - 1];
		vert3.vn = normals[atoi(verticesdata[index][2].c_str()) - 1];
	}

	vert.p = verts[atoi(verticesdata[0][0].c_str()) - 1];
	vert2.p = verts[atoi(verticesdata[index - 1][0].c_str()) - 1];
	vert3.p = verts[atoi(verticesdata[index][0].c_str()) - 1];

	vert.fn = Graphics::getNormal(vert.p, vert2.p, vert3.p);
	vert2.fn = Graphics::getNormal(vert.p, vert2.p, vert3.p);
	vert3.fn = Graphics::getNormal(vert.p, vert2.p, vert3.p);

	mesh.vertices.push_back(vert);
	mesh.vertices.push_back(vert2);
	mesh.vertices.push_back(vert3);
}
