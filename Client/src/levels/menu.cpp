#include "menu.hpp"

#include <sstream>

#include "..\logic\engine.hpp"
#include "..\utils.hpp"
#include "arena.hpp"

namespace lys
{

	Menu::Menu(EngineInternals &internals, const EngineLoadingArgs &args)
		: Level(internals, args, 60), _test(Sprite(Vector3(10, 10, 0), Vector2(200, 200), Vector4(1, 1, 1, 1), &_tex)), _tex("data/images/spectrum.jpg"), _label(nullptr, Vector3(0, 0, 1))
	{
		_label.repaint(internals);
	}

	void Menu::update(EngineInternals &internals, EngineArgs &args)
	{
		std::stringstream ss;
		ss << u8"FPS カッパ 卡帕 카파: " << internals.counter.getFPS(args.time.current);
		_label.setText(ss.str());
		_label.repaint(internals);

		if (internals.window.getButton(SDL_BUTTON_LEFT))
		{
			auto mousepos = internals.window.getMouse();
			mousepos.y = internals.window.getSize().y - mousepos.y;
			if ((mousepos.x >= _test.position.x) && (mousepos.x <= _test.position.x + _test.size.x))
			{
				if ((mousepos.y >= _test.position.y) && (mousepos.y <= _test.position.y + _test.size.y))
				{
					internals.engine.changeLevel<Arena>();
					return;
				}
			}
		}
	}

	void Menu::draw(EngineInternals &internals, EngineArgs &args)
	{
		_interface.submit(&_test);
		_interface.submit(&_label);

		_interface.renderBatch();
	}

	void Menu::resize(EngineInternals &internals)
	{
		_interface.resize(internals.window.getSize());
		_label.setPosition(Vector3(10, internals.window.getSize().y - (float)_label.getHeight() - 10, _label.getPosition().z));
	}

}