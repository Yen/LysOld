#pragma once

#include "..\logic\level.hpp"
#include "..\graphics\shaderprogram.hpp"
#include "..\graphics\layer\ui\uilayer.hpp"
#include "..\graphics\layer\ui\elements\uilabel.hpp"
#include "..\graphics\layer\ui\elements\uiprogressbar.hpp"

namespace lys
{

	class LoadingScreen : public Level
	{
	private:
		TypeEngine _typeEngine;
		UILayer _ui;
		UILabel _label;
		UIProgressBar _bar;

		std::string _loadingText;
		std::string _loadingTextCurrent;

		float _progress;
		float _progressCurrent;
	public:
		LoadingScreen(EngineInternals &internals, const EngineLoadingArgs &args);

		void setLoadingText(const std::string &loadingText);
		void setProgress(const float &progress);

		void update(EngineInternals &internals, EngineArgs &args) override;
		void draw(EngineInternals &internals, EngineArgs &args) override;
		void resize(EngineInternals &internals) override;
	};

}