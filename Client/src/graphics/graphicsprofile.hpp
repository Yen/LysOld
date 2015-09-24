#pragma once

#include <GL\glew.h>

namespace lys
{

	class GraphicsProfile
	{
	private:
		unsigned short _maxTextureSlots;
	public:
		GraphicsProfile();

		const unsigned short &getMaxTextureSlots() const;
	};

}