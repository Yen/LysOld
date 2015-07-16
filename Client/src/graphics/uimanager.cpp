#include "uimanager.hpp"

#include "..\utils.hpp"
#include "framebuffer.hpp"

namespace lys
{
	UIManager::UIManager()
	{
		LYS_LOG("Creating new uimanager (%d max elements in buffer)", LYS_UI_MAX_ELEMENTS);

		std::vector<ShaderData> shaders;
		shaders.push_back(ShaderData(GL_VERTEX_SHADER, utils::readFile("data/shaders/ui.vert")));
		shaders.push_back(ShaderData(GL_FRAGMENT_SHADER, utils::readFile("data/shaders/ui.frag")));
		_shader = new ShaderProgram(shaders);
		_shader->enable();

		int tids[LYS_UI_MAX_TEXTURES];
		for (int i = 0; i < LYS_UI_MAX_TEXTURES; i++)
		{
			tids[i] = i;
		}

		_shader->setUniform1iv("uni_textures", LYS_UI_MAX_TEXTURES, tids);

		glGenVertexArrays(1, &_vao);
		glBindVertexArray(_vao);

		glGenBuffers(1, &_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);

		LYS_LOG("Allocating uimanager array buffer [%d] bytes", LYS_UI_BUFFER_SIZE);
		glBufferData(GL_ARRAY_BUFFER, LYS_UI_BUFFER_SIZE, nullptr, GL_DYNAMIC_DRAW);

		glEnableVertexAttribArray(LYS_UI_SHADER_POSITION);
		glEnableVertexAttribArray(LYS_UI_SHADER_COLOR);
		glEnableVertexAttribArray(LYS_UI_SHADER_COORD);
		glEnableVertexAttribArray(LYS_UI_SHADER_TEXTURE);

		glVertexAttribPointer(LYS_UI_SHADER_POSITION, 3, GL_FLOAT, GL_FALSE, LYS_UI_VERTEX_SIZE, (const GLvoid *)(offsetof(UIVertex, position)));
		glVertexAttribPointer(LYS_UI_SHADER_COLOR, 4, GL_FLOAT, GL_FALSE, LYS_UI_VERTEX_SIZE, (const GLvoid *)(offsetof(UIVertex, color)));
		glVertexAttribPointer(LYS_UI_SHADER_COORD, 2, GL_FLOAT, GL_FALSE, LYS_UI_VERTEX_SIZE, (const GLvoid *)(offsetof(UIVertex, coord)));
		glVertexAttribPointer(LYS_UI_SHADER_TEXTURE, 1, GL_FLOAT, GL_FALSE, LYS_UI_VERTEX_SIZE, (const GLvoid *)(offsetof(UIVertex, texture)));

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindVertexArray(0);

		GLuint indices[LYS_UI_INDICES_COUNT];

		int offset = 0;
		for (int i = 0; i < LYS_UI_INDICES_COUNT; i += 6)
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

		LYS_LOG("Allocating uimanager index buffer [%d] bytes", sizeof(GLuint) * LYS_UI_INDICES_COUNT);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * LYS_UI_INDICES_COUNT, indices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		_defaultTexture = new Texture("data/images/uiDefault.png");

		begin();
	}

	UIManager::~UIManager()
	{
		glDeleteBuffers(1, &_ibo);
		glDeleteBuffers(1, &_vbo);
		glDeleteVertexArrays(1, &_vao);
		delete _shader;
	}

	void UIManager::push(UIElement *element)
	{
		if (_textureCount >= LYS_UI_MAX_TEXTURES)
		{
			flush();
		}

		float tid;

		const Texture *working = element->texture;
		if (working == nullptr)
		{
			working = _defaultTexture;
		}

		const Texture **tex = std::find(_textures, _textures + _textureCount, working);
		if (tex != _textures + _textureCount)
		{
			tid = (float)std::distance(_textures, tex);
		}
		else
		{
			tid = (float)_textureCount;
			_textures[_textureCount] = working;
			_textureCount++;
		}

		_buffer->position = element->position;
		_buffer->color = element->color;
		_buffer->coord = Vector2(0.0f, 0.0f);
		_buffer->texture = tid;
		_buffer++;

		_buffer->position = Vector3(element->position.x + element->size.x, element->position.y, element->position.z);
		_buffer->color = element->color;
		_buffer->coord = Vector2(1.0f, 0.0f);
		_buffer->texture = tid;
		_buffer++;

		_buffer->position = Vector3(element->position.x + element->size.x, element->position.y + element->size.y, element->position.z);
		_buffer->color = element->color;
		_buffer->coord = Vector2(1.0f, 1.0f);
		_buffer->texture = tid;
		_buffer++;

		_buffer->position = Vector3(element->position.x, element->position.y + element->size.y, element->position.z);
		_buffer->color = element->color;
		_buffer->coord = Vector2(0.0f, 1.0f);
		_buffer->texture = tid;
		_buffer++;

		_elementCount++;
	}

	void UIManager::flush()
	{
		end();

		draw();

		begin();
	}

	void UIManager::resize(const Metric2 &size)
	{
		_shader->enable();
		_shader->setUniformMat4("uni_pr_matrix", Matrix4::orthographic(0, (float)size.x, 0, (float)size.y, -1, 100));
	}

	void UIManager::draw()
	{
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		_shader->enable();

		for (int i = 0; i < _textureCount; i++)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			_textures[i]->bind();
		}

		glBindVertexArray(_vao);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);

		glDrawElements(GL_TRIANGLES, _elementCount * 6, GL_UNSIGNED_INT, nullptr);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void UIManager::begin()
	{
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		_buffer = (UIVertex *)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		_elementCount = 0;
		_textureCount = 0;
	}

	void UIManager::end()
	{
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		glUnmapBuffer(GL_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

}