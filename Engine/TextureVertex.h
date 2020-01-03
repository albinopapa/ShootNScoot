#pragma once

#include "Vec2.h"

struct TextureVertex
{
	constexpr TextureVertex operator+( TextureVertex const& rhs )const noexcept
	{
		return{ position + rhs.position, texcoord + rhs.texcoord };
	}
	constexpr TextureVertex operator-( TextureVertex const& rhs )const noexcept
	{
		return{ position - rhs.position, texcoord - rhs.texcoord };
	}
	constexpr TextureVertex operator*( float rhs )const noexcept
	{
		return{ position * rhs, texcoord * rhs };
	}
	friend constexpr TextureVertex operator*( float lhs, TextureVertex const& rhs )noexcept
	{
		return{ lhs * rhs.position, lhs * rhs.texcoord };
	}

	Vec2 position;
	Vec2 texcoord;
};

