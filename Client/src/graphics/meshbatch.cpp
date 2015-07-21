#include "meshbatch.hpp"

#include <algorithm>

#include "..\utils.hpp"

namespace lys
{

	static ShaderProgram createShader()
	{
		std::vector<ShaderData> shaders;
		shaders.push_back(ShaderData(GL_VERTEX_SHADER, utils::readFile("data/shaders/meshbatch.vert")));
		shaders.push_back(ShaderData(GL_FRAGMENT_SHADER, utils::readFile("data/shaders/meshbatch.frag")));
		return ShaderProgram(shaders);
	}

	MeshBatch::MeshBatch()
		: _shader(createShader()), _defaultTexture(Texture("data/images/meshDefault.png"))
	{
		_shader.enable();
		_shader.setUniformMat4("uni_vw_matrix", Matrix4::lookAt(Vector3(0, 2, 5), Vector3(0, 0, 0), Vector3(0, 1, 0)));
		int textureIDs[LYS_MESHBATCH_MAX_TEXTURES];
		for (int i = 0; i < LYS_MESHBATCH_MAX_TEXTURES; i++)
		{
			textureIDs[i] = i;
		};
		_shader.setUniform1iv("uni_textures", LYS_MESHBATCH_MAX_TEXTURES, textureIDs);

		glGenVertexArrays(1, &_vao);
		glBindVertexArray(_vao);

		glGenBuffers(1, &_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);

		glBufferData(GL_ARRAY_BUFFER, LYS_MESHBATCH_BUFFER_SIZE, nullptr, GL_DYNAMIC_DRAW);

		glEnableVertexAttribArray(LYS_MESHBATCH_SHADER_POSITION);
		glEnableVertexAttribArray(LYS_MESHBATCH_SHADER_COLOR);
		glEnableVertexAttribArray(LYS_MESHBATCH_SHADER_TEXTURE);
		glEnableVertexAttribArray(LYS_MESHBATCH_SHADER_COORDS);

		glVertexAttribPointer(LYS_MESHBATCH_SHADER_POSITION, 3, GL_FLOAT, GL_FALSE, LYS_MESHBATCH_VERTEX_SIZE, (const GLvoid *)(offsetof(MeshVertex, position)));
		glVertexAttribPointer(LYS_MESHBATCH_SHADER_COLOR, 4, GL_FLOAT, GL_FALSE, LYS_MESHBATCH_VERTEX_SIZE, (const GLvoid *)(offsetof(MeshVertex, color)));
		glVertexAttribPointer(LYS_MESHBATCH_SHADER_TEXTURE, 1, GL_FLOAT, GL_FALSE, LYS_MESHBATCH_VERTEX_SIZE, (const GLvoid *)(offsetof(MeshVertex, texture)));
		glVertexAttribPointer(LYS_MESHBATCH_SHADER_COORDS, 2, GL_FLOAT, GL_FALSE, LYS_MESHBATCH_VERTEX_SIZE, (const GLvoid *)(offsetof(MeshVertex, coords)));

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindVertexArray(0);

		glGenBuffers(1, &_ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, LYS_MESHBATCH_MAX_INDICES * sizeof(MeshBatchIndice), nullptr, GL_DYNAMIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	MeshBatch::~MeshBatch()
	{
		glDeleteBuffers(1, &_ibo);
		glDeleteBuffers(1, &_vbo);
		glDeleteVertexArrays(1, &_vao);
	}

	void MeshBatch::submit(const MeshData *mesh)
	{
		_meshes.push_back(mesh);
	}

	static bool compare(const MeshData *left, const MeshData *right)
	{
		return (left->texture < right->texture);
	}

	void MeshBatch::renderBatch()
	{
		if (_meshes.empty())
		{
			return;
		}

		begin();

		_shader.enable();

		glEnable(GL_DEPTH_TEST);

		glDisable(GL_ALPHA_TEST);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		GLsizei vertexCount = 0;
		GLsizei indexCount = 0;
		unsigned char textureOffset = 0;

		std::sort(std::begin(_meshes), std::end(_meshes), compare);

		while (!_meshes.empty())
		{
			const MeshData *current = _meshes.front();
			_meshes.pop_front();

			if ((current->vertices.size() > LYS_MESHBATCH_MAX_VERTICES) || (current->indices.size() > LYS_MESHBATCH_MAX_INDICES))
			{
				continue;
			}

			if ((vertexCount + current->vertices.size() >= LYS_MESHBATCH_MAX_VERTICES) || (indexCount + current->indices.size() >= LYS_MESHBATCH_MAX_INDICES) || (textureOffset >= LYS_MESHBATCH_MAX_TEXTURES))
			{
				end();
				drawCall(indexCount, textureOffset);
				begin();

				vertexCount = 0;
				indexCount = 0;
				textureOffset = 0;
			}

			const Texture *texture;
			if (current->texture == nullptr)
			{
				texture = &_defaultTexture;
			}
			else
			{
				texture = current->texture;
			}

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

			for (MeshDataIndice index : current->indices)
			{
				*_indexBuffer = index + vertexCount;

				_indexBuffer++;
				indexCount++;
			}

			for (MeshData::MeshDataVertex vert : current->vertices)
			{
				_buffer->position = Vector4::transform(Vector4(vert.position, 1), current->modelMatrix).xyz;
				_buffer->color = current->color;
				_buffer->normal = vert.normal;
				_buffer->texture = textureID;
				_buffer->coords = vert.coords;

				_buffer++;
				vertexCount++;
			}
		}

		end();

		drawCall(indexCount, textureOffset);
	}

	void MeshBatch::resize(const Metric2 &size)
	{
		_shader.enable();
		_shader.setUniformMat4("uni_pr_matrix", Matrix4::perspectivefov(45, (float)size.x / (float)size.y, 1, 1000));
	}

	void MeshBatch::begin()
	{
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		_buffer = (MeshVertex *)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
		_indexBuffer = (MeshBatchIndice *)glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void MeshBatch::end()
	{
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		glUnmapBuffer(GL_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
		glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void MeshBatch::drawCall(const GLsizei &indexCount, const unsigned char &textureCount)
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