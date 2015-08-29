#pragma once

#include "window.hpp"

namespace lys
{

	class GraphicsContext
	{
	private:
		SDL_Window *_window;
		SDL_GLContext _context;

		int _swapInterval;
	public:
		GraphicsContext(Window &window);
		~GraphicsContext();

		void makeCurrent();

		const int &getSwapInterval() const;
		void setSwapInterval(const int &swapInterval);
	};

}