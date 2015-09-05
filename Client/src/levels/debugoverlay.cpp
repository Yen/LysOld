#include "debugoverlay.hpp"

#include "..\graphics\shaderprogram.hpp"

namespace lys
{

	DebugOverlay::DebugOverlay(EngineInternals &internals, const EngineLoadingArgs &args)
		: Level(internals, args)
	{}

	void DebugOverlay::draw(EngineInternals &internals, EngineArgs &args)
	{
		ShaderProgram::disable();

		glBegin(GL_QUADS);
		glVertex2f(-0.5f, -0.5f);
		glVertex2f( 0.5f, -0.5f);
		glVertex2f( 0.5f,  0.5f);
		glVertex2f(-0.5f,  0.5f);
		glEnd();
	}

}