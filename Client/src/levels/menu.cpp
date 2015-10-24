#include "menu.hpp"

#include <sstream>

#include "..\logic\engine.hpp"
#include "..\utils.hpp"
#include "arena.hpp"

namespace lys
{

	Menu::Menu(EngineInternals &internals, const EngineLoadingArgs &args)
		: Level(internals, args, 60),
		_ui(internals.profile),
		_label(Vector2(0, 2), UIElement::TOP_LEFT, Vector2(0, 0), internals.typeEngine, false),
		_button(Vector2(20, 20), UIElement::BOTTOM_LEFT, Vector2(2, 2), "data/images/spectrum.jpg")
	{
		_renderer.add(&_ui);

		_button.color.x = 0;
	}

	void Menu::update(EngineInternals &internals, EngineArgs &args)
	{
		std::stringstream ss;
		const FPSInfo &fps = internals.counter.getFPS(args.time.current);
		ss << u8"FPS 幀率 帧率: " << fps.fps << " (" << fps.delay << ")";
		_label.setText(ss.str());
		_label.repaint(internals, _ui);

		if (internals.window.getButton(SDL_BUTTON_LEFT))
		{
			auto mousepos = _ui.mouseToView(internals.window.getMouse());
			auto topLeft = _ui.calculateTopLeft(&_button, _ui.getSize());

			if ((mousepos.x >= topLeft.x) && (mousepos.x <= topLeft.x + _button.size.x))
			{
				if ((mousepos.y >= topLeft.y) && (mousepos.y <= topLeft.y + _button.size.y))
				{
					internals.engine.changeLevel<Arena>();
					return;
				}
			}
		}
	}

	void Menu::draw(EngineInternals &internals, EngineArgs &args)
	{
		_ui.push(_label);
		_ui.push(_button);

		_renderer.render();
	}

	void Menu::resize(EngineInternals &internals)
	{
		_ui.resize(internals.window.getSize());
		_label.repaint(internals, _ui);
	}

}