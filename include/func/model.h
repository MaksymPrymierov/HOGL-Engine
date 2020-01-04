#ifndef MODEL_H
#define MODEL_H

#include <GL/glew.h>

class Model
{
	private:
		unsigned int *vao_id;
		unsigned int *_vbo;
		unsigned int vertex_count;

	public:
		Model() = delete;
		Model(unsigned int *vao, unsigned int *vbo, unsigned int vertex);
		virtual ~Model();
		unsigned int vao() const { return *vao_id; }
		unsigned int vertexCount() const { return vertex_count; }
};

namespace model
{
	namespace
	{
		unsigned int * createVAO();
		unsigned int * createVBO();
		void dataToVBO(unsigned int * vbo, float * data);
	}

	Model * loadToVAO(float * positions, unsigned int vertex_count);
}

#endif
