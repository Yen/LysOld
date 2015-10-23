#pragma once

#include <GL\glew.h>
#include <string>

namespace lys
{

	class GraphicsProfile
	{
	private:
		unsigned short _maxTextureSlots;
		std::string _vendor;
		std::string _renderer;
		std::string _version;
	public:
		GraphicsProfile();

		const unsigned short &getMaxTextureSlots() const;
		const std::string &getVendor() const;
		const std::string &getRenderer() const;
		const std::string &getVersion() const;
	};

}