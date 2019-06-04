#pragma once
#include "../Math/Vec.h"

class Block
{
public:
	union
	{
		struct
		{
			float x1, y1, x2, y2;
		};
		float texCoords[4];
	};

	Vec3f posOffset;
	Vec3f size;

	enum class BlockType { FLOOR, CRATE, HIGH_CRATE, WALL, CEILING, NONE };

	Block();
};
