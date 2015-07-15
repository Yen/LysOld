#pragma once

#include <string>
#include <GL\glew.h>

namespace lys
{

	class Texture
	{
	private:
		GLuint _id;
		unsigned int _bits;
	public:
		Texture(const std::string &path, const GLenum &min, const GLenum &mag, const GLenum &wrapS, const GLenum &wrapT);
		Texture(const std::string &path);
		~Texture();

		void bind() const;
		void unbind() const;
	};

}