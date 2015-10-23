#include "graphicsprofile.hpp"

#include "..\lys.hpp"

namespace lys
{

	GraphicsProfile::GraphicsProfile()
	{
		GLint maxTextureImageUnits;
		glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &maxTextureImageUnits);
		_maxTextureSlots = maxTextureImageUnits;

		_vendor = (const char *)glGetString(GL_VENDOR);
		_renderer = (const char *)glGetString(GL_RENDERER);
		_version = (const char *)glGetString(GL_VERSION);
	}

	const unsigned short &GraphicsProfile::getMaxTextureSlots() const
	{
		return _maxTextureSlots;
	}

	const std::string &GraphicsProfile::getVendor() const
	{
		return _vendor;
	}

	const std::string &GraphicsProfile::getRenderer() const
	{
		return _renderer;
	}

	const std::string &GraphicsProfile::getVersion() const
	{
		return _version;
	}

}