#pragma once

#include "sprite.hpp"

namespace lys
{

	class MultiSprite
	{
	public:
		virtual const Sprite *getData() const = 0;
		virtual const size_t getCount() const = 0;
	};

}