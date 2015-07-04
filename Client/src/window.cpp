#include "window.hpp"

#include <sstream>
#include <GL\glew.h>

namespace lys
{
	Window::Window(const std::string &title, const Metric2 &size)
		: _title(title), _size(size)
	{
		LYS_LOG("Creating new window (%s)", _title.data());

		if (SDL_Init(SDL_INIT_VIDEO) != 0)
		{
			std::stringstream err;
			err << "Error initializing SDL (" << SDL_GetError() << ")";
			SDL_ClearError();
			throw std::exception(err.str().data());
		}

		{
			int error[3];

			error[0] = SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
			error[1] = SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, LYS_GL_MAJOR_VERSION);
			error[2] = SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, LYS_GL_MINOR_VERSION);

			if ((error[0] || error[1] || error[2]) != 0)
			{
				std::stringstream err;
				err << "Error setting OpenGL context attribute (" << SDL_GetError() << ")";
				SDL_ClearError();
				throw std::exception(err.str().data());
			}
		}

		_window = SDL_CreateWindow(_title.data(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _size.x, _size.y, SDL_WINDOW_OPENGL | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
		if (!_window)
		{
			std::stringstream err;
			err << "Error creating window (" << SDL_GetError() << ")";
			SDL_ClearError();
			throw std::exception(err.str().data());
		}

		_context = SDL_GL_CreateContext(_window);
		if (*SDL_GetError() != '\0')
		{
			std::stringstream err;
			err << "Error creating OpenGL context (" << SDL_GetError() << ")";
			SDL_ClearError();
			throw std::exception(err.str().data());
		}

		GLenum error = glewInit();
		if (error != GLEW_OK)
		{
			std::stringstream err;
			err << "Error initializing GLEW (" << glewGetErrorString(error) << ")";
			SDL_ClearError();
			throw std::exception(err.str().data());
		}

		GLint major, minor;
		glGetIntegerv(GL_MAJOR_VERSION, &major);
		glGetIntegerv(GL_MINOR_VERSION, &minor);

		LYS_LOG("Target OpenGL version (%d.%d), system version (%d.%d)", LYS_GL_MAJOR_VERSION, LYS_GL_MINOR_VERSION, major, minor);

		if (!(major > LYS_GL_MAJOR_VERSION)) if (minor < LYS_GL_MINOR_VERSION)
		{
			LYS_LOG_WARNING("Target OpenGL version not supported by your system");
		}

		SDL_GL_SetSwapInterval(0);
	}

	Window::~Window()
	{
		LYS_LOG("Destroying window");
		SDL_GL_DeleteContext(_context);
		SDL_DestroyWindow(_window);
	}
}