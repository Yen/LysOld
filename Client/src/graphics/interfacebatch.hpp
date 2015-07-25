#pragma once

#include <GL\glew.h>
#include <deque>

#include "sprite.hpp"
#include "shaderprogram.hpp"
#include "..\maths.hpp"

namespace lys
{

	class SpriteVertex
	{
	public:
		Vector3 position;
		Vector4 color;
		float textureID;
		Vector2 uv;
	};

#define LYS_INTERFACEBATCH_MAX_SPRITES		1000
#define LYS_INTERFACEBATCH_VERTEX_SIZE		sizeof(SpriteVertex)
#define LYS_INTERFACEBATCH_SPRITE_SIZE		LYS_INTERFACEBATCH_VERTEX_SIZE * 4
#define LYS_INTERFACEBATCH_BUFFER_SIZE		LYS_INTERFACEBATCH_SPRITE_SIZE * LYS_INTERFACEBATCH_MAX_SPRITES

#define LYS_INTERFACEBATCH_INDICES_COUNT	LYS_INTERFACEBATCH_MAX_SPRITES * 6

#define LYS_INTERFACEBATCH_MAX_TEXTURES		32

#if LYS_INTERFACEBATCH_INDICES_COUNT < 256
#define LYS_INTERFACEBATCH_INDICES_TYPE		GL_UNSIGNED_BYTE
#elif LYS_INTERFACEBATCH_INDICES_COUNT < 65536
#define LYS_INTERFACEBATCH_INDICES_TYPE		GL_UNSIGNED_SHORT
#else
#define LYS_INTERFACEBATCH_INDICES_TYPE		GL_UNSIGNED_INT
#endif

	typedef
#if LYS_INTERFACEBATCH_INDICES_TYPE == GL_UNSIGNED_BYTE
		GLubyte
#elif LYS_INTERFACEBATCH_INDICES_TYPE == GL_UNSIGNED_SHORT
		GLushort
#else
		GLuint
#endif
		InterfaceBatchIndice;

#define LYS_INTERFACEBATCH_SHADER_POSITION		0
#define LYS_INTERFACEBATCH_SHADER_COLOR			1
#define LYS_INTERFACEBATCH_SHADER_TEXTURE		2
#define LYS_INTERFACEBATCH_SHADER_COORDS		3

	class InterfaceBatch
	{
	private:
		GLuint _vao;
		GLuint _vbo;
		GLuint _ibo;
		std::deque<const Sprite *> _sprites;
		SpriteVertex *_buffer;
		const Texture *_textures[LYS_INTERFACEBATCH_MAX_TEXTURES];
		ShaderProgram _shader;
		Metric2 _size;
		Vector2 _depth;
	public:
		InterfaceBatch();
		~InterfaceBatch();

		void submit(const Sprite *sprite);
		void submit(const Sprite sprites[], const size_t &count);

		void renderBatch();

		void resize(const Metric2 &size);
		void setDepth(const Vector2 &depth);
	private:
		void begin();
		void end();
		void drawCall(const GLsizei &batchCount, const GLsizei &textureCount);
	};

}