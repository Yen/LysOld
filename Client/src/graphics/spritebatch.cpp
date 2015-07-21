#include "spritebatch.hpp"

#include <algorithm>

#include "..\utils.hpp"

namespace lys
{

	static ShaderProgram createShader()
	{
		std::vector<ShaderData> shaders;
		shaders.push_back(ShaderData(GL_VERTEX_SHADER, utils::readFile("data/shaders/spritebatch.vert")));
		shaders.push_back(ShaderData(GL_FRAGMENT_SHADER, utils::readFile("data/shaders/spritebatch.frag")));
		return ShaderProgram(shaders);
	}

	SpriteBatch::SpriteBatch()
		: _shader(createShader()), _defaultTexture(Texture("data/images/spriteDefault.png"))
	{
		int textureIDs[LYS_SPRITEBATCH_MAX_TEXTURES];
		for (int i = 0; i < LYS_SPRITEBATCH_MAX_TEXTURES; i++)
		{
			textureIDs[i] = i;
		};
		_shader.enable();
		_shader.setUniform1iv("uni_textures", LYS_SPRITEBATCH_MAX_TEXTURES, textureIDs);

		glGenVertexArrays(1, &_vao);
		glBindVertexArray(_vao);

		glGenBuffers(1, &_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);

		glBufferData(GL_ARRAY_BUFFER, LYS_SPRITEBATCH_BUFFER_SIZE, nullptr, GL_DYNAMIC_DRAW);

		glEnableVertexAttribArray(LYS_SPRITEBATCH_SHADER_POSITION);
		glEnableVertexAttribArray(LYS_SPRITEBATCH_SHADER_COLOR);
		glEnableVertexAttribArray(LYS_SPRITEBATCH_SHADER_TEXTURE);
		glEnableVertexAttribArray(LYS_SPRITEBATCH_SHADER_COORDS);

		glVertexAttribPointer(LYS_SPRITEBATCH_SHADER_POSITION, 3, GL_FLOAT, GL_FALSE, LYS_SPRITEBATCH_VERTEX_SIZE, (const GLvoid *)(offsetof(SpriteVertex, position)));
		glVertexAttribPointer(LYS_SPRITEBATCH_SHADER_COLOR, 4, GL_FLOAT, GL_FALSE, LYS_SPRITEBATCH_VERTEX_SIZE, (const GLvoid *)(offsetof(SpriteVertex, color)));
		glVertexAttribPointer(LYS_SPRITEBATCH_SHADER_TEXTURE, 1, GL_FLOAT, GL_FALSE, LYS_SPRITEBATCH_VERTEX_SIZE, (const GLvoid *)(offsetof(SpriteVertex, texture)));
		glVertexAttribPointer(LYS_SPRITEBATCH_SHADER_COORDS, 2, GL_FLOAT, GL_FALSE, LYS_SPRITEBATCH_VERTEX_SIZE, (const GLvoid *)(offsetof(SpriteVertex, coords)));

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindVertexArray(0);

		SpriteBatchIndice indices[LYS_SPRITEBATCH_INCICES_COUNT];

		SpriteBatchIndice offset = 0;
		for (SpriteBatchIndice i = 0; i < LYS_SPRITEBATCH_INCICES_COUNT; i += 6)
		{
			indices[i + 0] = offset + 0;
			indices[i + 1] = offset + 1;
			indices[i + 2] = offset + 2;

			indices[i + 3] = offset + 2;
			indices[i + 4] = offset + 3;
			indices[i + 5] = offset + 0;

			offset += 4;
		}

		glGenBuffers(1, &_ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(SpriteBatchIndice) * LYS_SPRITEBATCH_INCICES_COUNT, indices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	SpriteBatch::~SpriteBatch()
	{
		glDeleteBuffers(1, &_ibo);
		glDeleteBuffers(1, &_vbo);
		glDeleteVertexArrays(1, &_vao);
	}

	void SpriteBatch::submit(const SpriteData *sprite)
	{
		_sprites.push_back(sprite);
	}

	void SpriteBatch::submit(const SpriteInterface *spriteInterface)
	{
		for (unsigned short i = 0; i < spriteInterface->getSpriteCount(); i++)
		{
			_sprites.push_back(&spriteInterface->getSpriteData()[i]);
		}
	}

	static bool compare(const SpriteData *left, const SpriteData *right)
	{
		return (left->texture < right->texture);
	}

	void SpriteBatch::renderBatch()
	{
		if (_sprites.empty())
		{
			return;
		}

		begin();

		_shader.enable();

		glEnable(GL_CULL_FACE);
		glFrontFace(GL_CCW);
		glCullFace(GL_BACK);

		glEnable(GL_DEPTH_TEST);

		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		GLsizei batchCount = 0;
		unsigned char textureOffset = 0;

		std::sort(std::begin(_sprites), std::end(_sprites), compare);

		while (!_sprites.empty())
		{
			const SpriteData *current = _sprites.front();
			_sprites.pop_front();

			// If sprite is not on screen skip it

			if ((current->position.x > _size.x) || (current->position.y > _size.y))
			{
				continue;
			}
			else if ((current->position.x + current->size.x < 0) || (current->position.y + current->size.y < 0))
			{
				continue;
			}

			// If all texture slots are full, draw then reset

			if ((textureOffset >= LYS_SPRITEBATCH_MAX_TEXTURES) || (batchCount >= LYS_SPRITEBATCH_MAX_SPRITES))
			{
				end();
				drawCall(batchCount * 6, textureOffset);
				begin();

				batchCount = 0;
				textureOffset = 0;
			}

			// If sprite texture is null, use default texture

			const Texture *texture;
			if (current->texture == nullptr)
			{
				texture = &_defaultTexture;
			}
			else
			{
				texture = current->texture;
			}

			// Set next texture in array to sprites texture

			float textureID;

			const Texture **result = std::find(_textures, _textures + textureOffset, texture);

			if (result != _textures + textureOffset)
			{
				textureID = (float)std::distance(_textures, result);
			}
			else
			{
				_textures[textureOffset] = texture;
				textureID = (float)textureOffset;
				textureOffset++;
			}

			_buffer[0].position = current->position;
			_buffer[0].color = current->color;
			_buffer[0].texture = textureID;
			_buffer[0].coords = Vector2(0, 0);

			_buffer[1].position = Vector3(current->position.x + current->size.x, current->position.y, current->position.z);
			_buffer[1].color = current->color;
			_buffer[1].texture = textureID;
			_buffer[1].coords = Vector2(1, 0);

			_buffer[2].position = Vector3(current->position.x + current->size.x, current->position.y + current->size.y, current->position.z);
			_buffer[2].color = current->color;
			_buffer[2].texture = textureID;
			_buffer[2].coords = Vector2(1, 1);

			_buffer[3].position = Vector3(current->position.x, current->position.y + current->size.y, current->position.z);
			_buffer[3].color = current->color;
			_buffer[3].texture = textureID;
			_buffer[3].coords = Vector2(0, 1);

			_buffer += 4;

			batchCount++;
		}

		end();

		drawCall(batchCount * 6, textureOffset);
	}

	void SpriteBatch::resize(const Metric2 &size)
	{
		_size = size;
		_shader.enable();
		_shader.setUniformMat4("uni_pr_matrix", Matrix4::orthographic(0, (float)_size.x, 0, (float)_size.y, -1, 100));
	}

	void SpriteBatch::begin()
	{
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		_buffer = (SpriteVertex *)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void SpriteBatch::end()
	{
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		glUnmapBuffer(GL_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void SpriteBatch::drawCall(const GLsizei &indexCount, const unsigned char &textureCount)
	{
		for (unsigned char i = 0; i < textureCount; i++)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			_textures[i]->bind();
		}

		glBindVertexArray(_vao);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);

		glDrawElements(GL_TRIANGLES, indexCount, LYS_MESHBATCH_INDICES_TYPE, nullptr);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

}