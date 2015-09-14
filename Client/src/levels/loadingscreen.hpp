#pragma once

#include "..\logic\level.hpp"
#include "..\graphics\shaderprogram.hpp"

namespace lys
{

	class LoadingScreen : public Level
	{
	private:
		ShaderProgram _shader;
		GLuint _vao;
		GLuint _vbo;
		GLuint _ibo;
	public:
		LoadingScreen(EngineInternals &internals, const EngineLoadingArgs &args);
		~LoadingScreen();

		void draw(EngineInternals &internals, EngineArgs &args) override;
		void resize(EngineInternals &internals) override;
	};

}