#pragma once

#include "shaderprogram.hpp"
#include "uielement.hpp"

namespace lys
{

	class UIVertex
	{
	public:
		Vector3 position;
		Vector4 color;
		Vector2 coord;
		float texture;
	};

#define LYS_UI_MAX_ELEMENTS			2500
#define LYS_UI_VERTEX_SIZE			sizeof(UIVertex)
#define LYS_UI_ELEMENT_SIZE			LYS_UI_VERTEX_SIZE * 4
#define LYS_UI_INDICES_COUNT		LYS_UI_MAX_ELEMENTS * 6
#define LYS_UI_BUFFER_SIZE			LYS_UI_ELEMENT_SIZE * LYS_UI_MAX_ELEMENTS

#define LYS_UI_SHADER_POSITION		0
#define LYS_UI_SHADER_COLOR			1
#define LYS_UI_SHADER_COORD			2
#define LYS_UI_SHADER_TEXTURE		3

#define LYS_UI_MAX_TEXTURES			32

	class UIManager
	{
	private:
		ShaderProgram *_shader;
		GLuint _vao;
		GLuint _vbo;
		GLuint _ibo;
		UIVertex *_buffer;
		GLsizei _elementCount;
		GLsizei _textureCount;
		Texture *_defaultTexture;
		Texture *_textures[LYS_UI_MAX_TEXTURES];
	public:
		UIManager();
		~UIManager();

		void push(UIElement *element);
		void flush();

		void resize(const Metric2 &size);
	private:
		void draw();
		void begin();
		void end();
	};

}