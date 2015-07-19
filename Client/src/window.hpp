#pragma once

#include <SDL2\SDL.h>

#include "lys.hpp"
#include "maths.hpp"

#define LYS_GL_MAJOR_VERSION 3
#define LYS_GL_MINOR_VERSION 3

#define LYS_BUTTON_COUNT 16
#define LYS_KEY_COUNT SDL_NUM_SCANCODES

namespace lys
{

	enum WindowMessage
	{
		NOTHING,
		CLOSE,
		MOUSEMOTION,
		BUTTONDOWN,
		BUTTONUP,
		KEYDOWN,
		KEYUP,
		FOCUSGAINED,
		FOCUSLOST,
		WINDOWMOVED,
		WINDOWSIZECHANGED
	};

	class Window
	{
	private:
		SDL_Window *_window;
		SDL_GLContext _context;
		SDL_Event _event;
	private:
		std::string _title;
		Metric2 _size;
		bool _visible;
		Metric2 _position;
		bool _focus;
		int _swapInterval;
		Metric2 _mouse;
		bool _buttons[LYS_BUTTON_COUNT];
		bool _keys[LYS_KEY_COUNT];
	public:
		Window(const std::string &title, const Metric2 &size, const bool &visible);
		~Window();

		void makeCurrent();
		void swapBuffers();
		bool pollMessages(WindowMessage &message);

		const std::string &getTitle() const;
		void setTitle(const std::string &title);

		const Metric2 &getSize() const;
		void setSize(const Metric2 &size);

		const bool &getVisible() const;
		void setVisible(const bool &visible);

		const Metric2 &getPosition() const;
		void setPosition(const Metric2 &position);

		const bool &getFocus() const;
		void setFocus(const bool &focus);

		const int &getSwapInterval() const;
		void setSwapInterval(const int &swapInterval);

		const Metric2 &getMouse() const;
		void setMouse(const Metric2 &mouse);

		const bool &getButton(const unsigned int &button) const;
		const bool &getKey(const unsigned int &key) const;
	};

}