#include "arena.hpp"

#include "..\logic\engine.hpp"

namespace lys
{

	Arena::Arena(EngineInternals &internals, const EngineLoadingArgs &args)
		: Level(internals, args)
	{
	}

	void Arena::draw(EngineInternals &internals, EngineArgs &args)
	{
		ShaderProgram::disable();

		glBegin(GL_QUADS);
		glVertex2f(-0.5, -0.5);
		glVertex2f( 0.5, -0.5);
		glVertex2f( 0.5,  0.5);
		glVertex2f(-0.5,  0.5);
		glEnd();
	}

}