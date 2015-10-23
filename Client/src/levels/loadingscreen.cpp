#include "loadingscreen.hpp"

#include <GL\glew.h>

#include "..\utils.hpp"
#include "..\logic\engine.hpp"

namespace lys
{

	LoadingScreen::LoadingScreen(EngineInternals &internals, const EngineLoadingArgs &args)
		: Level(internals, args, 32),
		_ui(internals.profile),
		_label(Vector2(0, 2), UIElement::BOTTOM_LEFT, Vector2(2, 2), _typeEngine, false, "Loading")
	{
		_label.repaint(internals, _ui);
	}

	void LoadingScreen::setLoadingText(const std::string &text)
	{
		_loadingText = text;
	}

	void LoadingScreen::update(EngineInternals &internals, EngineArgs &args)
	{
		auto loadingText = _loadingText;
		if (loadingText != _loadingTextCurrent)
		{
			_loadingTextCurrent = loadingText;

			std::string text = "Loading";
			if (_loadingTextCurrent.size() > 0)
				text.append(": ").append(_loadingTextCurrent);

			_label.setText(text);
			_label.repaint(internals, _ui);
		}
	}

	void LoadingScreen::draw(EngineInternals &internals, EngineArgs &args)
	{
		_ui.push(_label);
		_ui.flush();
	}

	void LoadingScreen::resize(EngineInternals &internals)
	{
		_ui.resize(internals.window.getSize());
		_label.repaint(internals, _ui);
	}

}