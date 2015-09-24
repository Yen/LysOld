#include "graphicsprofile.hpp"

#include "..\lys.hpp"

namespace lys
{

	GraphicsProfile::GraphicsProfile()
	{
		GLint maxTextureImageUnits;
		glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &maxTextureImageUnits);
		_maxTextureSlots = maxTextureImageUnits;
	}

	const unsigned short &GraphicsProfile::getMaxTextureSlots() const
	{
		return _maxTextureSlots;
	}

}