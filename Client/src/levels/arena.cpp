#include "arena.hpp"

#include "..\logic\engine.hpp"

namespace lys
{

	Arena::Arena(EngineInternals &internals, const EngineLoadingArgs &args)
		: Level(internals, args), _ui(internals.profile),
		_test{ { Vector2(20, 20), UIElement::Alignment::TOP_LEFT, Vector2(0, 0) }, { Vector2(20, 20), UIElement::Alignment::TOP_LEFT, Vector2(40, 80) } }
	{
	}

	void Arena::draw(EngineInternals &internals, EngineArgs &args)
	{
		_ui.pushArray(_test, 2);
		_ui.flush();
	}

	void Arena::resize(EngineInternals &internals)
	{
		_ui.resize(internals.window.getSize());
	}

}