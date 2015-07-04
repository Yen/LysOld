#pragma once

#include <SDL\SDL.h>

#include "lys.hpp"
#include "maths.hpp"

#define LYS_GL_MAJOR_VERSION 3
#define LYS_GL_MINOR_VERSION 2

namespace lys
{

	class Window
	{
	private:
		SDL_Window *_window;
		SDL_GLContext _context;
		SDL_Event _event;
	private:
		std::string _title;
		Metric2 _size;
	public:
		Window(const std::string &title, const Metric2 &size);
		~Window();
	};

}