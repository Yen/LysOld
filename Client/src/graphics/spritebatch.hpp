#pragma once

#include <deque>
#include <GL\glew.h>

#include "..\maths.hpp"
#include "..\graphics\shaderprogram.hpp"
#include "..\graphics\texture.hpp"

namespace lys
{

	class SpriteData
	{
	public:
		Vector3 position;
		Vector2 size;
		Vector4 color;
		const Texture *texture;
	public:
		bool operator <(SpriteData const &other) { return texture < other.texture; }
	};

	class SpriteVertex
	{
	public:
		Vector3 position;
		Vector4 color;
		float texture;
		Vector2 coords;
	};

#define LYS_SPRITEBATCH_MAX_SPRITES		1000
#define LYS_SPRITEBATCH_INCICES_COUNT	LYS_SPRITEBATCH_MAX_SPRITES * 6
#define LYS_SPRITEBATCH_MAX_TEXTURES	32

#if LYS_SPRITEBATCH_INCICES_COUNT < 256
#define LYS_SPRITEBATCH_INDICES_TYPE	GL_UNSIGNED_BYTE
	typedef GLubyte SpriteBatchIndice;
#elif LYS_SPRITEBATCH_INCICES_COUNT < 65536
#define LYS_SPRITEBATCH_INDICES_TYPE	GL_UNSIGNED_SHORT
	typedef GLushort SpriteBatchIndice;
#else
#define LYS_SPRITEBATCH_INDICES_TYPE	GL_UNSIGNED_INT
	typedef GLuint SpriteBatchIndice;
#endif

#define LYS_SPRITEBATCH_VERTEX_SIZE		sizeof(SpriteVertex)
#define LYS_SPRITEBATCH_SPRITE_SIZE		LYS_SPRITEBATCH_VERTEX_SIZE * 4
#define LYS_SPRITEBATCH_BUFFER_SIZE		LYS_SPRITEBATCH_SPRITE_SIZE * LYS_SPRITEBATCH_MAX_SPRITES

#define LYS_SPRITEBATCH_SHADER_POSITION		0
#define LYS_SPRITEBATCH_SHADER_COLOR		1
#define LYS_SPRITEBATCH_SHADER_TEXTURE		2
#define LYS_SPRITEBATCH_SHADER_COORDS		3

	class SpriteBatch
	{
	public:
		std::deque<const SpriteData *>_sprites;
		ShaderProgram *_shader;
		GLuint _vao;
		GLuint _vbo;
		GLuint _ibo;
		Metric2 _size;
		SpriteVertex *_buffer;
		const Texture *_defaultTexture;
		const Texture *_textures[LYS_SPRITEBATCH_MAX_TEXTURES];
	public:
		SpriteBatch();
		~SpriteBatch();

		void submit(const SpriteData *sprite);
		void renderBatch();

		void resize(const Metric2 &size);
	private:
		void begin();
		void end();
		void drawCall(const GLsizei &indexCount, const unsigned char &textureCount);
	};

}