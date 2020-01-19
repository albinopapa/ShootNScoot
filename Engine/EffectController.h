#pragma once

#include "Surface.h"

class EffectController
{
public:
	template<typename Effect>
	static void VSSetVertexBuffer( Effect& model, std::array<typename Effect::Vertex, 4> const& vertices )noexcept
	{
		std::copy( vertices.begin(), vertices.end(), model.vertices.begin() );
	}
	template<typename Effect, typename ConstantBuffer = typename Effect::VertexShader::ConstantBuffer>
	static void VSSetConstantBuffer( Effect& model, ConstantBuffer const& buffer_ )noexcept
	{
		model.vs.buffer = buffer_;
	}

	template<typename Effect, typename ConstantBuffer = typename Effect::PixelShader::ConstantBuffer>
	static void PSSetConstantBuffer( Effect& model, ConstantBuffer const& buffer_ )noexcept
	{
		model.ps.buffer = buffer_;
	}

	template<typename Effect>
	static void PSSetTexture( Effect& model, Surface const& sprite_ )noexcept
	{
		model.ps.sprite = std::addressof( sprite_ );
	}


};