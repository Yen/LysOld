#include "debugoverlay.hpp"

#include "..\graphics\shaderprogram.hpp"

namespace lys
{

	void DebugOverlay::draw(EngineCore &core, const FixedTimerData &time)
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