#pragma once

#include <GL\glew.h>
#include <deque>

#include "..\layer.hpp"
#include "uielement.hpp"
#include "..\..\graphicsprofile.hpp"
#include "..\..\shaderprogram.hpp"

namespace lys
{

#define LYS_UILAYER_RATIO_SIZE		64

	class VertexData
	{
	public:
		Vector3 position;
		Vector2 uv;
		float tid;
	};

#define LYS_UILAYER_MAX_ELEMENTS		1000
#define LYS_UILAYER_VERTEX_DATA_SIZE	sizeof(VertexData)
#define LYS_UILAYER_ELEMENT_SIZE		LYS_UILAYER_VERTEX_DATA_SIZE * 4
#define LYS_UILAYER_BUFFER_SIZE			LYS_UILAYER_ELEMENT_SIZE * LYS_UILAYER_MAX_ELEMENTS

#define LYS_UILAYER_INDICES_COUNT		LYS_UILAYER_MAX_ELEMENTS * 6

#if LYS_UILAYER_INDICES_COUNT < 256
#define LYS_UILAYER_INDICES_TYPE		GL_UNSIGNED_BYTE
#elif LYS_UILAYER_INDICES_COUNT < 65536
#define LYS_UILAYER_INDICES_TYPE		GL_UNSIGNED_SHORT
#else
#define LYS_UILAYER_INDICES_TYPE		GL_UNSIGNED_INT
#endif

	typedef
#if LYS_UILAYER_INDICES_TYPE == GL_UNSIGNED_BYTE
		GLubyte
#elif LYS_UILAYER_INDICES_TYPE == GL_UNSIGNED_SHORT
		GLushort
#else
		GLuint
#endif
		UILayerIndice;

#define LYS_UILAYER_SHADER_POSITION		0
#define LYS_UILAYER_SHADER_UV			1
#define LYS_UILAYER_SHADER_TID			2

	class UILayer : public Layer<UIElement>
	{
	private:
		ShaderProgram _shader;
		std::deque<const UIElement *> _elements;
		VertexData *_buffer;
		unsigned short _maxTextures;
		std::vector<const Texture2D *> _textures;
		GLuint _vao;
		GLuint _vbo;
		GLuint _ibo;
		Vector2 _ratioSize;
	public:
		UILayer(const GraphicsProfile &profile);
		~UILayer();

		void push(UIElement &data) override;

		void flush() override;

		void resize(const Metric2 &size);
	private:
		void parseElement(GLsizei &batchCount, GLsizei &textureCount, const UIElement *element, const Vector2 &size, const Vector2 &topLeft);
		void begin();
		void end();
		void drawCall(const GLsizei &batchCount, const GLsizei &textureCount);
	};

}