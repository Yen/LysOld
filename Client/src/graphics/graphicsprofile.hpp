#pragma once

#include <GL\glew.h>
#include <string>

namespace lys
{

	class GraphicsProfile
	{
	private:
		std::string _vendor;
		std::string _renderer;
		std::string _version;

		unsigned short _maxTextureSlots;
		unsigned short _maxSamples;
	public:
		GraphicsProfile();

		const std::string &getVendor() const;
		const std::string &getRenderer() const;
		const std::string &getVersion() const;

		const unsigned short &getMaxTextureSlots() const;
		const unsigned short &getMaxSamples() const;
	};

}