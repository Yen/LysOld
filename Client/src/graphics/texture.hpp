#pragma once

#include <string>
#include <GL\glew.h>

#include "..\maths.hpp"

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
		Texture(const Metric2 &size);
		Texture(const Metric2 &size, const void *pixels, const GLenum &format);
		~Texture();

		void bind() const;
		void unbind() const;

		const GLuint &getID() const;
	};

}