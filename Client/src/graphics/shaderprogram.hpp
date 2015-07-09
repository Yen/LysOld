#pragma once

#include <string>
#include <vector>
#include <GL\glew.h>

namespace lys
{

	typedef std::pair<GLenum, std::string> ShaderData;

	class ShaderProgram
	{
	private:
		GLuint _id;
	public:
		ShaderProgram(const std::vector<ShaderData> &shaders);
		~ShaderProgram();

		void enable() const;
		static void disable();
	};

}