#pragma once

#include <queue>

#include "shaderprogram.hpp"
#include "uielement.hpp"
#include "..\window.hpp"
#include "..\logic\fixedtimer.hpp"

namespace lys
{

	class UIVertex
	{
	public:
		Vector3 position;
		Vector4 color;
		Vector2 coord;
	};

#define LYS_UI_MAX_ELEMENTS			1000
#define LYS_UI_VERTEX_SIZE			sizeof(UIVertex)
#define LYS_UI_ELEMENT_SIZE			LYS_UI_VERTEX_SIZE * 4
#define LYS_UI_INDICES_COUNT		LYS_UI_MAX_ELEMENTS * 6
#define LYS_UI_BUFFER_SIZE			LYS_UI_ELEMENT_SIZE * LYS_UI_MAX_ELEMENTS

#define LYS_UI_SHADER_POSITION		0
#define LYS_UI_SHADER_COLOR			1
#define LYS_UI_SHADER_COORD			2

	class UIManager
	{
	private:
		std::queue<UIElement *> _elements;
		ShaderProgram *_shader;
		GLuint _vao;
		GLuint _vbo;
		GLuint _ibo;
		UIVertex *_buffer;
		GLsizei _elementCount;
	public:
		UIManager();
		~UIManager();

		void push(UIElement *element);
		void flush(Window *window, const FixedTimerData &time);

		void begin();
		void end();

		void resize(const Metric2 &size);
	private:
		void draw();
	};

}