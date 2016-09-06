/*
 * GLApplication.cpp
 *
 *  Created on: 07/08/2016
 *      Author: rey
 */

#include "Headers/GLApplication.h"

InputManager GLApplication::inputManager;
GLuint VBO, VAO, EBO;
Shader shader;


GLApplication::GLApplication() :
		windowManager(nullptr) {
}

GLApplication::~GLApplication() {
	destroy();
}

void GLApplication::GLMain() {
	initialize();
	applicationLoop();
}

void GLApplication::initialize() {
	if (!windowManager
			|| !windowManager->initialize(800, 700, "Tarea2_Ej7", false)) {
		this->destroy();
		exit(-1);
	}

	glViewport(0, 0, WindowManager::screenWidth, WindowManager::screenHeight);
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	shader.initialize("Shaders/basic.vs", "Shaders/basic.fs");

	// Set up vertex data (and buffer(s)) and attribute pointers
	

	/*Intento numero 1 de dibujar un cubo*/
	GLfloat vertices[] = {
		//CARA FRONTAL
		// Positions          // Colors
		0.3f, 0.3f, 0.0f, 1.0f, 0.0f, 0.0f, // Top Right
		0.3f, -0.3f, 0.0f, 0.0f, 1.0f, 0.0f, // Bottom Right
		-0.3f, -0.3f, 0.0f, 0.0f, 0.0f, 1.0f, // Bottom Left
		-0.3f, 0.3f, 0.0f, 1.0f, 1.0f, 0.0f, // Top Left
		//CARA DERECHA
		0.3f,-0.3f,-0.6f,0.0f,0.0f,1.0f, //v4
		0.3f,0.3f,-0.6f,1.0f,1.0f,0.0f, //v5
		//CARA IZQUIERDA
		-0.3f,0.3f,-0.6f,1.0f,0.0f,0.0f,//v6
		-0.3f,-0.3f,-0.6f,0.0f,1.0f,0.0f,//v7
	
	};
	GLuint indices[] = {  // Note that we start from 0!
		0, 1, 3, // First Triangle
		1, 2, 3,  // Second Triangle
		//DERECHA
		5, 4, 1,
		0, 5, 1,
		//IZQUIERDA
		3, 2, 7,
		7, 6, 3,
		//TRASERA
		7, 4, 5,
		6, 7, 5,
		//SUPERIOR
		6, 5, 0,
		3, 6, 0,
		//INFERIOR
		7, 1, 4,
		1, 7, 2

	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
	GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat),
			(GLvoid*) 0);
	glEnableVertexAttribArray(0);
	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat),
			(GLvoid*) (3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO
}

void GLApplication::applicationLoop() {
	bool processInput = true;
	double lastTime = TimeManager::Instance().GetTime();
	while (processInput) {
		processInput = windowManager->processInput(true);
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

		shader.turnOn();

		GLfloat timeValue = TimeManager::Instance().GetTime() - lastTime;
		// Create transformations
		glm::mat4 transform;
		//transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));
		transform = glm::translate(transform, glm::vec3(0.0f, 0.0f, 0.0f));
		
		/*if (InputManager::rotar == true){
			transform = glm::rotate(transform, 10.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		}*/

		//transform = glm::rotate(transform, (GLfloat) timeValue * 5.0f,
				//glm::vec3(0.0f, 1.0f, 0.0f));
		//transform = glm::rotate(transform, 10.0f,glm::vec3(1.0f, 0.0f, 0.0f));
		transform = inputManager.getTransform();

		// Get matrix's uniform location and set matrix
		GLint transformLoc = shader.getUniformLocation("transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE,
				glm::value_ptr(transform));

		glBindVertexArray(VAO);
		glEnable(GL_CULL_FACE);
		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		glDisable(GL_CULL_FACE);
		glBindVertexArray(0);

		shader.turnOff();

		windowManager->swapTheBuffers();
	}
}

void GLApplication::destroy() {
	if (windowManager) {
		delete windowManager;
		windowManager = nullptr;
	}

	shader.destroy();

	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &VBO);

	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VAO);
}
 