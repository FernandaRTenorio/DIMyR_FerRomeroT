#ifndef CUBO_H_
#define CUBO_H_
#include <vector>

#define _USE_MATH_DEFINES
#include <math.h>
#include <glm/glm.hpp>
#include <GL/glew.h>

typedef struct _VertexColorNormal {

	_VertexColorNormal() {
	}

	_VertexColorNormal(glm::vec3 position, glm::vec3 colorl, glm::vec3 normal) {
		this->position = position;
		this->color = colorl;
		this->normal = normal;
	}

	glm::vec3 position;
	glm::vec3 color;
	glm::vec3 normal;
} VertexColorNormals;

class Cubo {
public:
	Cubo(float alto, float ancho, bool mode);
	void init();
	void load();
	void render();
	virtual ~Cubo();
private:
	std::vector<VertexColorNormals> vertex;
	std::vector<GLuint> index;
	//float length;
	float alto;
	float ancho;
	bool mode;

	GLuint VAO, VBO, EBO;
};

#endif
