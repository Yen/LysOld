#pragma once

#include "..\logic\level.hpp"
#include "..\graphics\shaderprogram.hpp"
#include "..\graphics\layer\ui\uilayer.hpp"
#include "..\graphics\layer\ui\elements\uilabel.hpp"

namespace lys
{

	class LoadingScreen : public Level
	{
	private:
		TypeEngine _typeEngine;
		UILayer _ui;
		UILabel _label;

		std::string _loadingText;
		std::string _loadingTextCurrent;
	public:
		LoadingScreen(EngineInternals &internals, const EngineLoadingArgs &args);

		void setLoadingText(const std::string &loadingText = std::string());

		void update(EngineInternals &internals, EngineArgs &args) override;
		void draw(EngineInternals &internals, EngineArgs &args) override;
		void resize(EngineInternals &internals) override;
	};

}