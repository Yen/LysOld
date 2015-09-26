#include "loadingscreen.hpp"

#include <GL\glew.h>

#include "..\utils.hpp"
#include "..\logic\engine.hpp"

namespace lys
{

	static ShaderProgram createShader()
	{
		std::vector<ShaderData> shaders;
		shaders.push_back(ShaderData(GL_VERTEX_SHADER, ShaderProgram::createShaderList(utils::readFile("data/shaders/loadingscreen-v.glsl"))));
		shaders.push_back(ShaderData(GL_FRAGMENT_SHADER, ShaderProgram::createShaderList(utils::readFile("data/shaders/loadingscreen-f.glsl"))));
		return ShaderProgram(shaders);
	}

	LoadingScreen::LoadingScreen(EngineInternals &internals, const EngineLoadingArgs &args)
		: Level(internals, args), _shader(createShader())
	{
		_shader.enable();
		_shader.setUniformMat4("uni_vw_matrix", Matrix4::lookAt(Vector3(0, 0, 5), Vector3(0, 0, 0), Vector3(0, 1, 0)));

		glGenVertexArrays(1, &_vao);
		glBindVertexArray(_vao);

		glGenBuffers(1, &_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 3, nullptr);

		GLfloat vertices[12]
		{
			-2, -2, 0,
			-2,  2, 0,
			 2,  2, 0,
			 2, -2, 0
		};

		glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 12, vertices, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindVertexArray(0);

		glGenBuffers(1, &_ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);

		GLubyte indices[4]
		{
			0, 1, 3, 2
		};

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte) * 4, &indices, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	LoadingScreen::~LoadingScreen()
	{
		glDeleteBuffers(1, &_ibo);
		glDeleteBuffers(1, &_vbo);
		glDeleteVertexArrays(1, &_vao);
	}

	void LoadingScreen::draw(EngineInternals &internals, EngineArgs &args)
	{
		//TODO: Cube with lighting or something

		glDisable(GL_CULL_FACE);

		_shader.enable();
		_shader.setUniformMat4("uni_ml_matrix", Matrix4::rotation((float)args.time.current * 45, Vector3(0, 1, 0)));

		glBindVertexArray(_vao);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);

		glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE, nullptr);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void LoadingScreen::resize(EngineInternals &internals)
	{
		_shader.enable();
		_shader.setUniformMat4("uni_pr_matrix", Matrix4::perspectivefov(90, (float)internals.window.getSize().x / (float)internals.window.getSize().y, 1, 100));
	}

}