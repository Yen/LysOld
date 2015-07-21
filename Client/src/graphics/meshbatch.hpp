#pragma once

#include <GL\glew.h>
#include <deque>
#include <vector>

#include "..\maths.hpp"
#include "shaderprogram.hpp"

namespace lys
{

	class MeshData
	{
	public:
		struct MeshDataVertex
		{
			Vector3 position;
			Vector3 normal;
			Vector2 coord;
		};
	public:
		std::vector<MeshDataVertex> vertices;
		std::vector<unsigned short> indices;
	};

	class MeshVertex
	{
	public:
		Vector3 position;
		Vector3 normal;
		Vector2 coord;
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

#define LYS_MESHBATCH_SHADER_POSITION		0
#define LYS_MESHBATCH_SHADER_COLOR			1
#define LYS_MESHBATCH_SHADER_TEXTURE		2
#define LYS_MESHBATCH_SHADER_COORDS			3

	class MeshBatch
	{
	private:
		std::deque<const MeshData *> _meshes;
		ShaderProgram _shader;
		GLuint _vao;
		GLuint _vbo;
		GLuint _ibo;
		MeshVertex *_buffer;
		MeshBatchIndice *_indexBuffer;
	public:
		MeshBatch();
		~MeshBatch();

		void submit(const MeshData *mesh);
		void renderBatch();

		void resize(const Metric2 &size);
	private:
		void begin();
		void end();
		void drawCall(const GLsizei &indexCount, const unsigned char &textureCount);
	};

}