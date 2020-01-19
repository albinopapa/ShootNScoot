#pragma once

#include "Bencher.h"
#include <string>

class BencherController
{
public:
	static void Start( Bencher& model )noexcept;
	static bool End( Bencher& model )noexcept;
	static std::wstring String( Bencher const& model )noexcept;
};