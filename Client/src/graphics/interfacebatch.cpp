#include "interfacebatch.hpp"

#include <algorithm>

#include "..\utils.hpp"

namespace lys
{

	static ShaderProgram createShader()
	{
		std::vector<ShaderData> shaders;
		shaders.push_back(ShaderData(GL_VERTEX_SHADER, utils::readFile("data/shaders/interfacebatch.vert")));
		shaders.push_back(ShaderData(GL_FRAGMENT_SHADER, utils::readFile("data/shaders/interfacebatch.frag")));
		return ShaderProgram(shaders);
	}

	InterfaceBatch::InterfaceBatch()
		: _shader(createShader()), _depth(Vector2(-1, 100))
	{
		int textureIDs[LYS_INTERFACEBATCH_MAX_TEXTURES];
		for (int i = 0; i < LYS_INTERFACEBATCH_MAX_TEXTURES; i++)
		{
			textureIDs[i] = i;
		};
		_shader.enable();
		_shader.setUniform1iv("uni_textures", LYS_INTERFACEBATCH_MAX_TEXTURES, textureIDs);

		glGenVertexArrays(1, &_vao);
		glBindVertexArray(_vao);

		glGenBuffers(1, &_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);

		glBufferData(GL_ARRAY_BUFFER, LYS_INTERFACEBATCH_BUFFER_SIZE, nullptr, GL_DYNAMIC_DRAW);

		glEnableVertexAttribArray(LYS_INTERFACEBATCH_SHADER_POSITION);
		glEnableVertexAttribArray(LYS_INTERFACEBATCH_SHADER_COLOR);
		glEnableVertexAttribArray(LYS_INTERFACEBATCH_SHADER_TEXTURE);
		glEnableVertexAttribArray(LYS_INTERFACEBATCH_SHADER_COORDS);

		glVertexAttribPointer(LYS_INTERFACEBATCH_SHADER_POSITION, 3, GL_FLOAT, GL_FALSE, LYS_INTERFACEBATCH_VERTEX_SIZE, (const GLvoid *)(offsetof(SpriteVertex, position)));
		glVertexAttribPointer(LYS_INTERFACEBATCH_SHADER_COLOR, 4, GL_FLOAT, GL_FALSE, LYS_INTERFACEBATCH_VERTEX_SIZE, (const GLvoid *)(offsetof(SpriteVertex, color)));
		glVertexAttribPointer(LYS_INTERFACEBATCH_SHADER_TEXTURE, 1, GL_FLOAT, GL_FALSE, LYS_INTERFACEBATCH_VERTEX_SIZE, (const GLvoid *)(offsetof(SpriteVertex, textureID)));
		glVertexAttribPointer(LYS_INTERFACEBATCH_SHADER_COORDS, 2, GL_FLOAT, GL_FALSE, LYS_INTERFACEBATCH_VERTEX_SIZE, (const GLvoid *)(offsetof(SpriteVertex, uv)));

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindVertexArray(0);

		InterfaceBatchIndice indices[LYS_INTERFACEBATCH_INDICES_COUNT];

		InterfaceBatchIndice offset = 0;
		for (InterfaceBatchIndice i = 0; i < LYS_INTERFACEBATCH_INDICES_COUNT; i += 6)
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

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(InterfaceBatchIndice) * LYS_INTERFACEBATCH_INDICES_COUNT, indices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	InterfaceBatch::~InterfaceBatch()
	{
		glDeleteBuffers(1, &_ibo);
		glDeleteBuffers(1 ,&_vbo);
		glDeleteVertexArrays(1, &_vao);
	}

	void InterfaceBatch::submit(const Sprite *sprite)
	{
		_sprites.push_back(sprite);
	}

	void InterfaceBatch::submit(const Sprite sprites[], const size_t &count)
	{
		for (size_t i = 0; i < count; i++)
		{
			submit(&sprites[i]);
		}
	}

	static bool compare(const Sprite *left, const Sprite *right)
	{
		return (left->texture < right->texture);
	}

	void InterfaceBatch::renderBatch()
	{
		if (_sprites.empty())
		{
			return;
		}

		_shader.enable();

		begin();

		glEnable(GL_CULL_FACE);
		glFrontFace(GL_CCW);
		glCullFace(GL_BACK);

		glEnable(GL_DEPTH_TEST);

		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		std::sort(std::begin(_sprites), std::end(_sprites), compare);

		GLsizei batchCount = 0;
		GLsizei textureCount = 0;

		while (!_sprites.empty())
		{
			if ((batchCount >= LYS_INTERFACEBATCH_MAX_SPRITES) || (textureCount >= LYS_INTERFACEBATCH_MAX_TEXTURES))
			{
				end();
				drawCall(batchCount, textureCount);
				begin();

				batchCount = 0;
				textureCount = 0;
			}

			const Sprite *&current = _sprites.front();

			if ((current->position.x > _size.x) || (current->position.y > _size.y))
			{
				_sprites.pop_front();
				continue;
			}
			else if ((current->position.x + current->size.x < 0) || (current->position.y + current->size.y < 0))
			{
				_sprites.pop_front();
				continue;
			}
			else if ((current->position.z <= _depth.x) || (current->position.z >= _depth.y))
			{
				_sprites.pop_front();
				continue;
			}

			float tid = -1.0f;
			if (current->texture != nullptr)
			{
				const Texture **result = std::find(_textures, _textures + textureCount, current->texture);

				if (result != _textures + textureCount)
				{
					tid = (float)std::distance(_textures, result);
				}
				else
				{
					_textures[textureCount] = current->texture;
					tid = (float)textureCount;
					textureCount++;
				}
			}

			_buffer[0].position = current->position;
			_buffer[0].color = current->color;
			_buffer[0].textureID = tid;
			_buffer[0].uv = current->uvs[0];

			_buffer[1].position = Vector3(current->position.x + current->size.x, current->position.y, current->position.z);
			_buffer[1].color = current->color;
			_buffer[1].textureID = tid;
			_buffer[1].uv = current->uvs[1];

			_buffer[2].position = Vector3(current->position.x + current->size.x, current->position.y + current->size.y, current->position.z);
			_buffer[2].color = current->color;
			_buffer[2].textureID = tid;
			_buffer[2].uv = current->uvs[2];

			_buffer[3].position = Vector3(current->position.x, current->position.y + current->size.y, current->position.z);
			_buffer[3].color = current->color;
			_buffer[3].textureID = tid;
			_buffer[3].uv = current->uvs[3];

			_buffer += 4;

			batchCount++;

			_sprites.pop_front();
		}

		end();
		drawCall(batchCount, textureCount);
	}

	void InterfaceBatch::resize(const Metric2 &size)
	{
		_size = size;
		_shader.enable();
		_shader.setUniformMat4("uni_pr_matrix", Matrix4::orthographic(0, (float)_size.x, 0, (float)_size.y, _depth.x, _depth.y));
	}

	void InterfaceBatch::setDepth(const Vector2 &depth)
	{
		_depth = depth;
		resize(_size);
	}

	void InterfaceBatch::begin()
	{
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		_buffer = (SpriteVertex *)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void InterfaceBatch::end()
	{
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		glUnmapBuffer(GL_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void InterfaceBatch::drawCall(const GLsizei &batchCount, const GLsizei &textureCount)
	{
		for (GLsizei i = 0; i < textureCount; i++)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			_textures[i]->bind();
		}

		glBindVertexArray(_vao);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);

		glDrawElements(GL_TRIANGLES, batchCount * 6, LYS_INTERFACEBATCH_INDICES_TYPE, nullptr);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

}