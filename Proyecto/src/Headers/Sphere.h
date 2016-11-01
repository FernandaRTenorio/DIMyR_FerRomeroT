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

#include "definition.h"

class Sphere {
public:
	Sphere(float ratio, int slices, int stacks, MODEL_MODE mode);
	void init();
	void init_para_sbb();
	void load();
	void load_sbb();
	void loadCube();
	void render();
	void render2();
	void renderCube();
	virtual ~Sphere();
private:
	std::vector<VertexColor> vertex;
	std::vector<VertexColor> vertex2;
	std::vector<VertexLightColor> vertexLC;
	std::vector<VertexLightTexture> vertexLT;
	std::vector<GLuint> index;
	std::vector<GLuint> index2;
	float ratio;
	int slices;
	int stacks;
	MODEL_MODE mode;
	GLuint VAO, VBO, EBO,texture;
};

#endif /* SPHERE_H_ */
