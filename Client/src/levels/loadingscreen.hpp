#pragma once

#include "..\logic\level.hpp"
#include "..\graphics\shaderprogram.hpp"

namespace lys
{

	class LoadingScreen : public Level
	{
	private:
		ShaderProgram _shader;
	public:
		LoadingScreen(const EngineLoadingArgs &args);

		void draw(EngineInternals &internals, EngineArgs &args) override;
		void resize(EngineInternals &internals) override;
	};

}