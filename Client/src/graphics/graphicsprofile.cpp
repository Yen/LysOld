#include "graphicsprofile.hpp"

#include "..\lys.hpp"

namespace lys
{

	GraphicsProfile::GraphicsProfile()
	{
		_vendor = (const char *)glGetString(GL_VENDOR);
		_renderer = (const char *)glGetString(GL_RENDERER);
		_version = (const char *)glGetString(GL_VERSION);

		GLint buffer;
		glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &buffer);
		_maxTextureSlots = buffer;
		glGetIntegerv(GL_MAX_SAMPLES, &buffer);
		_maxSamples = buffer;
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

	const unsigned short &GraphicsProfile::getMaxTextureSlots() const
	{
		return _maxTextureSlots;
	}

	const unsigned short &GraphicsProfile::getMaxSamples() const
	{
		return _maxSamples;
	}

}