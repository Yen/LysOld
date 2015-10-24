#include "loadingscreen.hpp"

#include <GL\glew.h>

#include "..\utils.hpp"
#include "..\logic\engine.hpp"

namespace lys
{

	LoadingScreen::LoadingScreen(EngineInternals &internals, const EngineLoadingArgs &args)
		: Level(internals, args, 60),
		_ui(internals.profile),
		_label(Vector2(0, 2), UIElement::BOTTOM_LEFT, Vector2(2, 6), _typeEngine, false, "Loading"),
		_bar(Vector2(_ui.getSize().x, 4), UIElement::BOTTOM_LEFT, Vector2(0, 0))
	{
		_renderer.add(&_ui);

		_label.repaint(internals, _ui);
		_bar.repaint(internals, _ui);
	}

	void LoadingScreen::setLoadingText(const std::string &text)
	{
		_loadingText = text;
	}

	void LoadingScreen::setProgress(const float &progress)
	{
		_progress = progress;
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

		auto progress = _progress;
		if (progress != _progressCurrent)
		{
			_progressCurrent = progress;

			_bar.setProgress(_progressCurrent);
			_bar.repaint(internals, _ui);
		}
	}

	void LoadingScreen::draw(EngineInternals &internals, EngineArgs &args)
	{
		_ui.push(_label);
		_ui.push(_bar);

		_renderer.render();
	}

	void LoadingScreen::resize(EngineInternals &internals)
	{
		_ui.resize(internals.window.getSize());
		_label.repaint(internals, _ui);

		_bar.size.x = _ui.getSize().x;
		_bar.repaint(internals, _ui);
	}

}