#include <func/model.h>

Model::Model(unsigned int *vao, unsigned int *vbo, unsigned int vertex) :
	vao_id(vao), _vbo(vbo), vertex_count(vertex)
{

}

Model::~Model()
{
	glDeleteVertexArrays(1, vao_id);
	glDeleteBuffers(1, _vbo);
}

namespace model
{
	namespace
	{
		unsigned int * createVAO()
		{
			unsigned int * vao = nullptr;
			glGenVertexArrays(1, vao);
			return vao;
		}

		unsigned int * createVBO()
		{
			unsigned int * vbo = nullptr;
			glGenBuffers(1, vbo);

			return vbo;
		}

		void dataToVBO(unsigned int * vbo, float * data)
		{
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (const void*)0);
			glEnableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
	}

	Model * loadToVAO(float * positions, unsigned int vertex_count)
	{
		unsigned int * vao = createVAO();
		unsigned int * vbo = createVBO();
		dataToVBO(vbo, positions);

		return new Model(vao, vbo, vertex_count);
	}
}
