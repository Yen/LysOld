#include "meshbatch.hpp"

#include "..\utils.hpp"

namespace lys
{

	MeshBatch::MeshBatch()
	{
		std::vector<ShaderData> shaders;
		shaders.push_back(ShaderData(GL_VERTEX_SHADER, utils::readFile("data/shaders/meshbatch.vert")));
		shaders.push_back(ShaderData(GL_FRAGMENT_SHADER, utils::readFile("data/shaders/meshbatch.frag")));
		_shader = new ShaderProgram(shaders);
		_shader->enable();
		_shader->setUniformMat4("uni_vw_matrix", Matrix4::lookAt(Vector3(0, 2, 5), Vector3(0, 0, 0), Vector3(0, 1, 0)));
	}

	MeshBatch::~MeshBatch()
	{
		delete _shader;
	}

	void MeshBatch::submit(const MeshData *mesh)
	{
		_meshes.push_back(mesh);
	}

	void MeshBatch::renderBatch()
	{
		if (_meshes.empty())
		{
			return;
		}

		_shader->enable();

		while (!_meshes.empty())
		{
			const MeshData *current = _meshes.front();
			_meshes.pop_front();

			glBegin(GL_QUADS);
			glVertex3i(0, 0, 0);
			glVertex3i(1, 0, 0);
			glVertex3i(1, 1, 0);
			glVertex3i(0, 1, 0);
			glEnd();
		}
	}

	void MeshBatch::resize(const Metric2 &size)
	{
		_shader->enable();
		_shader->setUniformMat4("uni_pr_matrix", Matrix4::perspectivefov(45, (float)size.x / (float)size.y, 1, 1000));
	}

}