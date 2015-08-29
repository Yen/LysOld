#include "graphicscontext.hpp"

#include <sstream>
#include <GL\glew.h>

namespace lys
{

	GraphicsContext::GraphicsContext(Window &window)
		:_window(window._window)
	{
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

		LYS_LOG("Graphics context created with target OpenGL version (%d.%d), system version (%d.%d)", LYS_GL_MAJOR_VERSION, LYS_GL_MINOR_VERSION, major, minor);
		if (!(major > LYS_GL_MAJOR_VERSION)) if (minor < LYS_GL_MINOR_VERSION)
		{
			LYS_LOG_WARNING("Target OpenGL version not supported by your system");
		}
	}

	GraphicsContext::~GraphicsContext()
	{
		SDL_GL_DeleteContext(_context);
	}

	void GraphicsContext::makeCurrent()
	{
		SDL_GL_MakeCurrent(_window, _context);
	}

	const int &GraphicsContext::getSwapInterval() const
	{
		return _swapInterval;
	}

	void GraphicsContext::setSwapInterval(const int &swapInterval)
	{
		_swapInterval = swapInterval;
		SDL_GL_SetSwapInterval(_swapInterval);
	}

}