#pragma once

#include <GL\glew.h>
#include <deque>

#include "..\maths.hpp"

namespace lys
{

	typedef unsigned short MeshDataCount;

	class MeshData
	{
	public:
		Vector3 *vertices;
		MeshDataCount verticesCount;

		unsigned short *indices;
		MeshDataCount indicesCount;
	};

	class MeshVertex
	{
	public:
		Vector3 position;
	};

#define LYS_MESHBATCH_MAX_VERTICES	1000
#define LYS_MESHBATCH_MAX_INDICES	LYS_MESHBATCH_MAX_VERTICES

#if LYS_MESHBATCH_MAX_INDICES < 256
#define LYS_MESHBATCH_INDICES_TYPE	GL_UNSIGNED_BYTE
#elif LYS_MESHBATCH_MAX_INDICES < 65536
#define LYS_MESHBATCH_INDICES_TYPE	GL_UNSIGNED_SHORT
#else
#define LYS_MESHBATCH_INDICES_TYPE	GL_UNSIGNED_INT
#endif

	typedef
#if LYS_MESHBATCH_INDICES_TYPE == GL_UNSIGNED_BYTE
		GLubyte
#elif LYS_MESHBATCH_INDICES_TYPE == GL_UNSIGNED_SHORT
		GLushort
#else
		GLuint
#endif
		MeshBatchIndice;

#define LYS_MESHBATCH_VERTEX_SIZE	sizeof(MeshVertex)
#define LYS_MESHBATCH_BUFFER_SIZE	LYS_MESHBATCH_VERTEX_SIZE * LYS_MESHBATCH_MAX_VERTICES

	class MeshBatch
	{
	private:
		std::deque<const MeshData *> _meshes;
	public:
		MeshBatch();
		~MeshBatch();

		void submit(const MeshData *mesh);
		void renderBatch();

		void resize(const Metric2 &size);
	};

}