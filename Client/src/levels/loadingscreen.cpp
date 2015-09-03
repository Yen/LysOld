#include "loadingscreen.hpp"

#include <GL\glew.h>

#include "..\utils.hpp"
#include "..\logic\engine.hpp"

namespace lys
{

	static ShaderProgram createShader()
	{
		std::vector<ShaderData> shaders;
		shaders.push_back(ShaderData(GL_VERTEX_SHADER, utils::readFile("data/shaders/loadingscreen.vert")));
		shaders.push_back(ShaderData(GL_FRAGMENT_SHADER, utils::readFile("data/shaders/loadingscreen.frag")));
		return ShaderProgram(shaders);
	}

	LoadingScreen::LoadingScreen(const EngineLoadingArgs &args)
		: Level(args), _shader(createShader())
	{
		_shader.enable();
		_shader.setUniformMat4("uni_vw_matrix", Matrix4::lookAt(Vector3(0, 0, 5), Vector3(0, 0, 0), Vector3(0, 1, 0)));
	}

	void LoadingScreen::draw(EngineInternals &internals, EngineArgs &args)
	{
		//TODO: Cube with lighting or something

		glDisable(GL_CULL_FACE);

		_shader.enable();
		_shader.setUniformMat4("uni_ml_matrix", Matrix4::rotation(args.time.current * 45, Vector3(0, 1, 0)));

		glBegin(GL_QUADS);
		glVertex3f(-2, -2, 0);
		glVertex3f( 2, -2, 0);
		glVertex3f( 2,  2, 0);
		glVertex3f(-2,  2, 0);
		glEnd();
	}

	void LoadingScreen::resize(EngineInternals &internals)
	{
		_shader.enable();
		_shader.setUniformMat4("uni_pr_matrix", Matrix4::perspectivefov(90, (float)internals.window.getSize().x / (float)internals.window.getSize().y, 1, 100));
	}

}