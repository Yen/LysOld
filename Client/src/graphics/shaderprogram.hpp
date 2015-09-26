#pragma once

#include <string>
#include <vector>
#include <GL\glew.h>
#include <map>

#include "..\maths.hpp"

namespace lys
{

	typedef std::vector<std::string> ShaderList;
	typedef std::pair<GLenum, ShaderList> ShaderData;
	typedef std::map<std::string, std::string> ShaderDefines;

	class ShaderProgram
	{
	private:
		GLuint _id;
	public:
		template <class ...A>
		static ShaderList createShaderList(const A &... args)
		{
			return ShaderList{ args... };
		}

		static std::string &processShaderSource(std::string &source, const ShaderDefines &defines);

		ShaderProgram(const std::vector<ShaderData> &shaders);
		~ShaderProgram();

		void enable() const;
		static void disable();

		void setUniform1f(const GLchar *name, float value);
		void setUniform1i(const GLchar *name, int value);
		void setUniform1d(const GLchar *name, double value);

		void setUniform1fv(const GLchar *name, int count, float *value);
		void setUniform1iv(const GLchar *name, int count, int *value);
		void setUniform1dv(const GLchar *name, int count, double *value);

		void setUniform2f(const GLchar *name, const Vector2 &value);
		void setUniform3f(const GLchar *name, const Vector3 &value);
		void setUniform4f(const GLchar *name, const Vector4 &value);

		void setUniformMat4(const GLchar *name, const Matrix4 &value);
	private:
		GLint getUniformLocation(const GLchar *name);
	};

}