#include "shaderprogram.hpp"

#include <sstream>
#include <boost\format.hpp>

#include "..\lys.hpp"

namespace lys
{

	std::string &ShaderProgram::processShaderSource(std::string &source, const ShaderDefines &defines)
	{
		for (auto x : defines)
		{
			std::string key = (boost::format("$%1%$") % x.first).str();
			bool searching = true;
			while (searching)
			{
				auto found = source.find(key);
				if (found == std::string::npos)
				{
					searching = false;
					continue;
				}

				source.replace(found, key.length(), x.second);
			}
		}
		return source;
	}

	ShaderProgram::ShaderProgram(const std::vector<ShaderData> &shaders)
	{
		_id = glCreateProgram();

		std::vector<GLuint> valid;

		for (std::vector<ShaderData>::const_iterator i = shaders.begin(); i != shaders.end(); i++)
		{
			std::vector<const char *> ssources;
			for (auto &x : i->second)
			{
				ssources.push_back(x.data());
			}

			GLuint shader = glCreateShader(i->first);

			glShaderSource(shader, (GLsizei)i->second.size(), ssources.data(), nullptr);
			glCompileShader(shader);

			GLint result;
			glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
			if (result == GL_FALSE)
			{
				GLint length;
				glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
				std::vector<char> error(length);
				glGetShaderInfoLog(shader, length, &length, &error[0]);
				glDeleteShader(shader);
				std::stringstream err;
				err << "Failed to compile shader (" << i->first << "):\n" << error.data();
				throw std::exception(err.str().data());
			}

			valid.push_back(shader);
		}

		for (std::vector<GLuint>::iterator i = valid.begin(); i != valid.end(); i++)
		{
			glAttachShader(_id, *i);
		}

		glLinkProgram(_id);
		glValidateProgram(_id);

		for (std::vector<GLuint>::iterator i = valid.begin(); i != valid.end(); i++)
		{
			glDeleteShader(*i);
		}
	}

	ShaderProgram::~ShaderProgram()
	{
		glDeleteProgram(_id);
	}

	void ShaderProgram::enable() const
	{
		glUseProgram(_id);
	}

	void ShaderProgram::disable()
	{
		glUseProgram(0);
	}

	void ShaderProgram::setUniform1f(const GLchar *name, float value)
	{
		glUniform1f(getUniformLocation(name), value);
	}

	void ShaderProgram::setUniform1i(const GLchar *name, int value)
	{
		glUniform1i(getUniformLocation(name), value);
	}

	void ShaderProgram::setUniform1d(const GLchar *name, double value)
	{
		glUniform1d(getUniformLocation(name), value);
	}

	void ShaderProgram::setUniform1fv(const GLchar *name, int count, float *value)
	{
		glUniform1fv(getUniformLocation(name), count, value);
	}

	void ShaderProgram::setUniform1iv(const GLchar *name, int count, int *value)
	{
		glUniform1iv(getUniformLocation(name), count, value);
	}

	void ShaderProgram::setUniform1dv(const GLchar *name, int count, double *value)
	{
		glUniform1dv(getUniformLocation(name), count, value);
	}

	void ShaderProgram::setUniform2f(const GLchar *name, const Vector2 &value)
	{
		glUniform2f(getUniformLocation(name), value.x, value.y);
	}

	void ShaderProgram::setUniform3f(const GLchar *name, const Vector3 &value)
	{
		glUniform3f(getUniformLocation(name), value.x, value.y, value.z);
	}

	void ShaderProgram::setUniform4f(const GLchar *name, const Vector4 &value)
	{
		glUniform4f(getUniformLocation(name), value.x, value.y, value.z, value.w);
	}

	void ShaderProgram::setUniformMat4(const GLchar *name, const Matrix4 &value)
	{
		glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, value.elements);
	}

	GLint ShaderProgram::getUniformLocation(const GLchar *name)
	{
		GLint location = glGetUniformLocation(_id, name);
		if (location == -1)
		{
			std::stringstream err;
			err << "Error identifying shader program uniform location (" << name << ")";
			throw std::exception(err.str().data());
		}
		return location;
	}

}