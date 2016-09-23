/*
 * Mesh.cpp
 *
 *  Created on: 13/09/2016
 *      Author: rey
 */

#include "Headers/Mesh.h"

/*Recibe un vector llamado vertices, indices, tecturas*/
Mesh::Mesh(std::vector<Vertex> vertices, std::vector<GLuint> indices,
		std::vector<Texture> textures) :
		vertices(vertices), indices(indices), textures(textures), VAO(0), VBO(
				0), EBO(0) {
	this->loadMesh();
}

Mesh::~Mesh() {
	/*glDisableVertexAttribArray(0);
	 glDisableVertexAttribArray(1);
	 glDisableVertexAttribArray(2);

	 glBindBuffer(GL_ARRAY_BUFFER, 0);
	 glDeleteBuffers(1, &VBO);

	 glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	 glDeleteBuffers(1, &EBO);

	 glBindVertexArray(0);
	 glDeleteVertexArrays(1, &VAO);*/
}

/*Este metodo renderiza y aplica texturas*/
void Mesh::render(Shader * shader) {
	// Bind appropriate textures
	//Declara enteros para cada componente
	GLuint diffuseNr = 1;
	GLuint specularNr = 1;
	GLuint normalNr = 1;
	GLuint heightNr = 1;
	for (GLuint i = 0; i < this->textures.size(); i++) { //recorre todo el arreglo de texturas 
		// Retrieve texture number (the N in diffuse_textureN)
		std::stringstream ss;
		std::string number;
		std::string name = this->textures[i].getType(); //asigna el tipo de textura en curso a la variable name
		/*Se evalua el tipo de la textura y segun el tipo va aumentando una variable correspondiente y la pasa a ss*/
		if (name == "texture_diffuse")
			ss << diffuseNr++; // Transfer GLuint to stream
		else if (name == "texture_specular")
			ss << specularNr++; // Transfer GLuint to stream
		else if (name == "texture_normal")
			ss << normalNr++; // Transfer GLuint to stream
		else if (name == "texture_height")
			ss << heightNr++; // Transfer GLuint to stream
		number = ss.str(); //Se pasa a number lo que contiene ss

		glUniform1i(shader->getUniformLocation((name + number).c_str()), i);//Le pasa al shader una variable que consiste en la textura
		// And finally bind the texture
		this->textures[i].bind(GL_TEXTURE0 + i); //enlaza la textura correspondiente
	}

	// Draw mesh
	glBindVertexArray(this->VAO);
	glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	// Always good practice to set everything back to defaults once configured.
	//Desenlaza todas las texturas
	for (GLuint i = 0; i < this->textures.size(); i++) {
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

/*Esta funcion inicializa los buffers y lee vertices, coordenadas de texturas, y normales*/
void Mesh::loadMesh() {
	// Create buffers/arrays
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);
	glGenBuffers(1, &this->EBO);

	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	// Load the data of mesh in the GPU
	glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex),
			&this->vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(GLuint),
			&this->indices[0], GL_STATIC_DRAW);

	// Set the vertex attribute pointers
	// Vertex Positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
			(GLvoid*) 0);
	// Vertex Normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
			(GLvoid*) offsetof(Vertex, Normal));
	// Vertex Texture Coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
			(GLvoid*) offsetof(Vertex, TexCoords));

	glBindVertexArray(0);
}

