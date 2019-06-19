#include "ObjectLoader.h"
#include <fstream>
#include <strstream>
#include <sstream>
#include <string>

static std::vector<std::string> split(const std::string& str, const char separator)
{
	std::vector<std::string> strings;
	std::istringstream f(str);
	std::string s;

	while (std::getline(f, s, separator))
		strings.push_back(s);

	return strings;
}

Graphics::Mesh ObjLoader::loadObj(const std::string& filename)
{
	Graphics::Mesh mesh;

	std::ifstream f(filename);
	if (!f.is_open())
		return mesh;

	std::vector<Vec3f> vertices;
	std::vector<Vec2f> textureCoords;
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
			vertices.push_back(v);
		}
		//Texture
		else if (line[0] == 'v' && line[1] == 't')
		{
			Vec2f vt;
			s >> junk >> junk >> vt.x >> vt.y;
			textureCoords.push_back(vt);
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
			auto remaining = line;
			remaining = remaining.substr(2, remaining.size());
			auto indices = split(remaining, ' ');

			std::vector<std::vector<std::string>> verticesData;
			for (auto i = 0; i < static_cast<int>(indices.size()); i++)
			{
				auto vertexData = split(indices[i], '/');
				verticesData.push_back(vertexData);
				if (i >= 2)
					addTriangle(mesh, vertices, textureCoords, normals, i, verticesData);
			}
		}
	}

	return mesh;
}

void ObjLoader::addTriangle(Graphics::Mesh &mesh,
	const std::vector<Vec3f> &vertices,
	const std::vector<Vec2f> &textureCoords,
	const std::vector<Vec3f> &normals,
	const int index,
	const std::vector<std::vector<std::string>> &verticesData) {
	Graphics::Vertex vertex1;
	Graphics::Vertex vertex2;
	Graphics::Vertex vertex3;

	if (!textureCoords.empty())
	{
		vertex1.vt = textureCoords[atoi(verticesData[0][1].c_str()) - 1];
		vertex2.vt = textureCoords[atoi(verticesData[index - 1][1].c_str()) - 1];
		vertex3.vt = textureCoords[atoi(verticesData[index][1].c_str()) - 1];
	}
	if (!normals.empty())
	{
		vertex1.vn = normals[atoi(verticesData[0][2].c_str()) - 1];
		vertex2.vn = normals[atoi(verticesData[index - 1][2].c_str()) - 1];
		vertex3.vn = normals[atoi(verticesData[index][2].c_str()) - 1];
	}

	vertex1.p = vertices[atoi(verticesData[0][0].c_str()) - 1];
	vertex2.p = vertices[atoi(verticesData[index - 1][0].c_str()) - 1];
	vertex3.p = vertices[atoi(verticesData[index][0].c_str()) - 1];

	vertex1.fn = Graphics::getNormal(vertex1.p, vertex2.p, vertex3.p);
	vertex2.fn = Graphics::getNormal(vertex1.p, vertex2.p, vertex3.p);
	vertex3.fn = Graphics::getNormal(vertex1.p, vertex2.p, vertex3.p);

	mesh.vertices.push_back(vertex1);
	mesh.vertices.push_back(vertex2);
	mesh.vertices.push_back(vertex3);
}
