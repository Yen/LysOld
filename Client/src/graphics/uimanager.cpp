#include "uimanager.hpp"

#include "..\utils.hpp"

namespace lys
{
	UIManager::UIManager()
	{
		LYS_LOG("Creating new uimanager");

		std::vector<ShaderData> shaders;
		shaders.push_back(ShaderData(GL_VERTEX_SHADER, utils::readFile("data/shaders/ui.vert")));
		shaders.push_back(ShaderData(GL_FRAGMENT_SHADER, utils::readFile("data/shaders/ui.frag")));
		_shader = new ShaderProgram(shaders);

		glGenVertexArrays(1, &_vao);
		glBindVertexArray(_vao);

		glGenBuffers(1, &_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);

		glBufferData(GL_ARRAY_BUFFER, LYS_UI_BUFFER_SIZE, nullptr, GL_DYNAMIC_DRAW);

		glEnableVertexAttribArray(LYS_UI_SHADER_POSITION);
		glEnableVertexAttribArray(LYS_UI_SHADER_COLOR);

		glVertexAttribPointer(LYS_UI_SHADER_POSITION, 3, GL_FLOAT, GL_FALSE, LYS_UI_VERTEX_SIZE, (const GLvoid *)(offsetof(UIVertex, position)));
		glVertexAttribPointer(LYS_UI_SHADER_COLOR, 4, GL_FLOAT, GL_FALSE, LYS_UI_VERTEX_SIZE, (const GLvoid *)(offsetof(UIVertex, color)));

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

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * LYS_UI_INDICES_COUNT, indices, GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
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
		_elements.push(element);
	}

	void UIManager::flush(Window *window, const FixedTimerData &time)
	{
		_count = 0;

		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		_buffer = (UIVertex *)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		while (!_elements.empty())
		{
			UIElement *working = _elements.front();

			_buffer->position = working->position;
			_buffer->color = working->color;
			_buffer++;

			_buffer->position = Vector3(working->position.x + working->size.x, working->position.y, working->position.z);
			_buffer->color = working->color;
			_buffer++;

			_buffer->position = Vector3(working->position.x + working->size.x, working->position.y + working->size.y, working->position.z);
			_buffer->color = working->color;
			_buffer++;

			_buffer->position = Vector3(working->position.x, working->position.y + working->size.y, working->position.z);
			_buffer->color = working->color;
			_buffer++;

			_count += 6;

			_elements.pop();
		}

		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		glUnmapBuffer(GL_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glEnable(GL_DEPTH_TEST);
		_shader->enable();

		glBindVertexArray(_vao);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);

		glDrawElements(GL_TRIANGLES, _count, GL_UNSIGNED_INT, nullptr);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	void UIManager::resize(const Metric2 &size)
	{
		_shader->enable();
		_shader->setUniformMat4("uni_pr_matrix", Matrix4::orthographic(0, (float)size.x, 0, (float)size.y, -1, 100));
	}
}