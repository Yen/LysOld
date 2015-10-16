#include "arena.hpp"

#include "..\logic\engine.hpp"
#include "..\graphics\texture2d.hpp"

namespace lys
{

	Arena::Arena(EngineInternals &internals, const EngineLoadingArgs &args)
		: Level(internals, args), _ui(internals.profile),
		_fb(internals.window.getSize()),
		_test1(Vector2(20, 20), UIElement::Alignment::TOP_LEFT, Vector2(5, 5), "data/images/spectrum.jpg"),
		_test2(Vector2(20, 20), UIElement::Alignment::TOP_RIGHT, Vector2(5, 5), "data/images/spectrum.jpg"),
		_test3(Vector2(20, 20), UIElement::Alignment::BOTTOM_RIGHT, Vector2(5, 5), "data/images/spectrum.jpg"),
		_test4(Vector2(20, 20), UIElement::Alignment::BOTTOM_LEFT, Vector2(5, 5), "data/images/spectrum.jpg")
	{
		Pixmap pixmapTest("data/images/spectrum.jpg");
		Texture2D texture2Dtest(pixmapTest);
	}

	void Arena::draw(EngineInternals &internals, EngineArgs &args)
	{
		_ui.push(_test1);
		_ui.push(_test2);
		_ui.push(_test3);
		_ui.push(_test4);
		_ui.flush();
	}

	void Arena::resize(EngineInternals &internals)
	{
		_ui.resize(internals.window.getSize());
	}

}