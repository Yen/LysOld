#include "meshbatch.hpp"

namespace lys
{

	MeshBatch::MeshBatch()
	{

	}

	MeshBatch::~MeshBatch()
	{

	}

	void MeshBatch::submit(const MeshData *mesh)
	{
		_meshes.push_back(mesh);
	}

	void MeshBatch::renderBatch()
	{

	}

	void MeshBatch::resize(const Metric2 &size)
	{

	}

}