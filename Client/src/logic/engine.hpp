#pragma once

#include "..\window.hpp"
#include "fixedtimer.hpp"
#include "..\graphics\spritebatch.hpp"
#include "..\graphics\meshbatch.hpp"

namespace lys
{

	class Engine
	{
	private:
		Window *_window;
		FixedTimer *_timer;
		SpriteBatch *_spriteBatch;
		MeshBatch *_meshBatch;
	public:
		Engine();
		~Engine();

		void run();
	};

}