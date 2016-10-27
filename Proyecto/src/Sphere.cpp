/*
 * Sphere.cpp
 *
 *  Created on: 06/09/2016
 *      Author: rey
 */

#include "Headers/Sphere.h"
//#include "Headers/Header.h"
struct VertexColorTexture {
	glm::vec3 m_Pos;
	glm::vec3 m_Color;
	glm::vec2 m_TexCoord;
};

Sphere::Sphere(float ratio, int slices, int stacks, MODEL_MODE mode) :
		ratio(ratio), slices(slices), stacks(stacks), VAO(0), VBO(0), EBO(0) {
}

Sphere::~Sphere() {

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	glDisableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &VBO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glDeleteBuffers(1, &EBO);

	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VAO);
	//glDeleteTextures(1, &texture);

}


void Sphere::init() {
	float porcentajex = 0;
	float porcentajey = 1;
	vertex.resize(((slices + 1) * (stacks + 1)));
	index.resize((slices * stacks + slices) * 6);
	for (int i = 0; i <= stacks; ++i) {
		float V = i / (float) stacks;
		float phi = V * M_PI;

		for (int j = 0; j <= slices; ++j) {
			float U = j / (float) slices;
			float theta = U * M_PI * 2.0;

			float X = ratio * cos(theta) * sin(phi);
			float Y = ratio * cos(phi);
			float Z = ratio * sin(theta) * sin(phi);

			vertex[i * (slices + 1) + j].position = glm::vec3(X, Y, Z);
			vertex[i * (slices + 1) + j].color = glm::vec3(0.0f, 1.0f, 0.0f);
			vertex[i * (slices + 1) + j].texture = glm::vec2(U, V);

			porcentajex = porcentajex + U;
		}

		porcentajey = porcentajey + V;
		porcentajex = 0;
	}

	for (int i = 0; i < slices * stacks + slices; ++i) {
		index[i * 6] = i;
		index[i * 6 + 1] = i + slices + 1;
		index[i * 6 + 2] = i + slices;
		index[i * 6 + 3] = i + slices + 1;
		index[i * 6 + 4] = i;
		index[i * 6 + 5] = i + 1;
	}
}

void Sphere::init_para_sbb(){
	
	vertex.resize(((slices + 1) * (stacks + 1)));
	index.resize((slices * stacks + slices) * 6);
	for (int i = 0; i <= stacks; ++i) {
		float V = i / (float)stacks;
		float phi = V * M_PI;

		for (int j = 0; j <= slices; ++j) {
			float U = j / (float)slices;
			float theta = U * M_PI * 2.0;

			float X = ratio * cos(theta) * sin(phi);
			float Y = ratio * cos(phi);
			float Z = ratio * sin(theta) * sin(phi);

			vertex[i * (slices + 1) + j].position = glm::vec3(X, Y, Z);
			vertex[i * (slices + 1) + j].color = glm::vec3(0.0f, 1.0f, 0.0f);
			

			
		}

	}

	for (int i = 0; i < slices * stacks + slices; ++i) {
		index[i * 6] = i;
		index[i * 6 + 1] = i + slices + 1;
		index[i * 6 + 2] = i + slices;
		index[i * 6 + 3] = i + slices + 1;
		index[i * 6 + 4] = i;
		index[i * 6 + 5] = i + 1;
	}
}

void Sphere::loadCube(AABB aabb){
	vertex2.resize(8);
	index.resize(36);
	vertex2[0].position = glm::vec3(-0.5f, -0.5f, 0.5f);
		//glm::vec3(aabb.min.x, aabb.min.y, aabb.min.z);
	vertex2[0].color = glm::vec3(0.0f,1.0f,0.0f);
	vertex2[1].position = glm::vec3(0.5f, -0.5f, 0.5f);
		//glm::vec3(aabb.max.x, aabb.min.y, aabb.min.z);
	vertex2[1].color = glm::vec3(0.0f, 1.0f, 0.0f);
	vertex2[2].position = glm::vec3(0.5f, 0.5f, 0.5f);
		//glm::vec3(aabb.max.x, aabb.max.y, aabb.min.z);
	vertex2[2].color = glm::vec3(0.0f, 1.0f, 0.0f);
	vertex2[3].position = glm::vec3(-0.5f, 0.5f, 0.5f);
		//glm::vec3(aabb.min.x, aabb.max.y, aabb.min.z);
	vertex2[3].color = glm::vec3(0.0f, 1.0f, 0.0f);

	vertex2[4].position = glm::vec3(-0.5f, -0.5f, -0.5f);
		//glm::vec3(aabb.min.x, aabb.min.y, aabb.max.z);
	vertex2[4].color = glm::vec3(0.0f, 1.0f, 0.0f);
	vertex2[5].position = glm::vec3(0.5f, -0.5f, -0.5f);
		//glm::vec3(aabb.max.x, aabb.min.y, aabb.max.z);
	vertex2[5].color = glm::vec3(0.0f, 1.0f, 0.0f);
	vertex2[6].position = glm::vec3(0.5f, 0.5f, -0.5f);
		//glm::vec3(aabb.max.x, aabb.max.y, aabb.max.z);
	vertex2[6].color = glm::vec3(0.0f, 1.0f, 0.0f);
	vertex2[7].position = glm::vec3(-0.5f, 0.5f, -0.5f);
		//glm::vec3(aabb.min.x, aabb.max.y, aabb.max.z);
	vertex2[7].color = glm::vec3(0.0f, 1.0f, 0.0f);

	
	//frontal
	index[0] = 0;
	index[1] = 1;
	index[2] = 3;
	index[3] = 1;
	index[4] = 2;
	index[5] = 3;
	//derecha
	index[6] = 5;
	index[7] = 4;
	index[8] = 1;
	index[9] = 0;
	index[10] = 5;
	index[11] = 1;
	//izquierda
	index[12] = 3;
	index[13] = 2;
	index[14] = 7;
	index[15] = 7;
	index[16] = 6;
	index[17] = 3;
	//trasera
	index[18] = 7;
	index[19] = 4;
	index[20] = 5;
	index[21] = 6;
	index[22] = 7;
	index[23] = 5;
	//superior
	index[24] = 6;
	index[25] = 5;
	index[26] = 0;
	index[27] = 3;
	index[28] = 6;
	index[29] = 0;
	//inferior
	index[30] = 7;
	index[31] = 1;
	index[32] = 4;
	index[33] = 1;
	index[34] = 7;
	index[35] = 2;


	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertex2.size() * ((sizeof(glm::vec3) * 2) + sizeof(glm::vec2)),
		vertex2.data(),
		GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index2.size() * sizeof(GLuint),
		index2.data(),
		GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex2[0]),
		(GLvoid*)0);
	glEnableVertexAttribArray(0);
	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex2[0]),
		(GLvoid*) sizeof(vertex2[0].position));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0); // Unbind VAO


}


void Sphere::load() {

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertex.size() * ((sizeof(glm::vec3) * 2) + sizeof(glm::vec2)),
			vertex.data(),
			GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index.size() * sizeof(GLuint),
			index.data(),
			GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex[0]),
			(GLvoid*) 0);
	glEnableVertexAttribArray(0);
	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex[0]),
			(GLvoid*) sizeof(vertex[0].position));
	glEnableVertexAttribArray(1);
	// Texture Mapping attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertex[0]),
		(GLvoid*)(sizeof(vertex[0].position) + sizeof(vertex[0].color)));
	glEnableVertexAttribArray(2);
	glBindVertexArray(0); // Unbind VAO

}

void Sphere::load_sbb() {

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertex.size() * ((sizeof(glm::vec3) * 2) + sizeof(glm::vec2)),
		vertex.data(),
		GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index.size() * sizeof(GLuint),
		index.data(),
		GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex[0]),
		(GLvoid*)0);
	glEnableVertexAttribArray(0);
	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex[0]),
		(GLvoid*) sizeof(vertex[0].position));
	glEnableVertexAttribArray(1);
	
	glBindVertexArray(0); // Unbind VAO

}


void Sphere::render() {

	glBindVertexArray(VAO);
	glDrawElements( GL_LINES, index.size(), GL_UNSIGNED_INT,
			(GLvoid*) (sizeof(GLuint) * 0));
	glBindVertexArray(0);

}

void Sphere::render2() {

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, index.size(), GL_UNSIGNED_INT,
		(GLvoid*)(sizeof(GLuint) * 0));
	glBindVertexArray(0);

}

void Sphere::renderCube(){
	

	glBindVertexArray(VAO);
	glEnable(GL_CULL_FACE);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	glDisable(GL_CULL_FACE);
	glBindVertexArray(0);
}
