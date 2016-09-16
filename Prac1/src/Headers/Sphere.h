/*
 * Sphere.h
 *
 *  Created on: 06/09/2016
 *      Author: rey
 */

#ifndef SPHERE_H_
#define SPHERE_H_

#include <vector>

#define _USE_MATH_DEFINES
#include <math.h>
#include <FreeImage.h>
#include <GL/glew.h>
#include "definition.h"
#include "WindowManager.h"

class Sphere {
public:
	Sphere(float ratio, int slices, int stacks);
	void init();
	void initCube();
	void load();
	void render();
	void renderCube();
	void loadCube();
	void deleteBuffers();
	virtual ~Sphere();
private:
	std::vector<VertexColor> vertex;
	std::vector<GLuint> index;
	std::vector<VertexColor> vertexCube;
	std::vector<GLuint> indexCube;
	float ratio;
	int slices;
	int stacks;

	GLuint VAO, VBO, EBO,VAO2,VBO2,EBO2, texture;


};

#endif /* SPHERE_H_ */
