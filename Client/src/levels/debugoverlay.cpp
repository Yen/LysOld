#include "debugoverlay.hpp"

#include "..\graphics\shaderprogram.hpp"

namespace lys
{

	DebugOverlay::DebugOverlay(const EngineLoadingArgs &args)
		: Level(args)
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