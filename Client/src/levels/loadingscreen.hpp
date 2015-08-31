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
		LoadingScreen();

		void draw(EngineCore &core, const FixedTimerData &time) override;
		void resize(EngineCore &core) override;
	};

}