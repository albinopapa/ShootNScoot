#pragma once

class RasterDefault {
public:
	constexpr Color operator()( Color color, Color bg )const noexcept {
		return color;
	}
};

class RasterAlpha {
public:
	constexpr Color operator()( Color color, Color bg )const noexcept {
		return AlphaBlend( color, bg );
	}
};

