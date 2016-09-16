/*
 * GLApplication.cpp
 *
 *  Created on: 07/08/2016
 *      Author: rey
 */

#include "Headers/GLApplication.h"

Sphere sphere(1, 20, 20);
Shader shader;

/*
//textura
GLuint texture;

struct VertexColorTexture {
	glm::vec3 m_Pos;
	glm::vec3 m_Color;
	glm::vec2 m_TexCoord;
};
*/


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
			|| !windowManager->initialize(800, 700, "Window GLFW", false)) {
		this->destroy();
		exit(-1);
	}

	glViewport(0, 0, WindowManager::screenWidth, WindowManager::screenHeight);
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	sphere.init();
	sphere.initCube();
	sphere.load();
	sphere.loadCube();

	

	shader.initialize("Shaders/Color.vs", "Shaders/Color.fs");

}

void GLApplication::applicationLoop() {
	bool processInput = true;
	double lastTime = TimeManager::Instance().GetTime();

	glm::vec3 posicionObjeto[] =
	{ glm::vec3(2, 5, -15), glm::vec3(7.0f, 2.0f, -5.0f) };


	while (processInput) {
		processInput = windowManager->processInput(true);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

		GLfloat timeValue = TimeManager::Instance().GetTime() - lastTime;

		shader.turnOn();

		// Create transformations
		glm::mat4 view;
		glm::mat4 projection;
		
		//INTENTO DE CAMARA EN TERCERA PERSONA
		// Create transformations
		//view = glm::rotate(view,
			//glm::radians(windowManager->inputManager.getPitch()),
			//glm::vec3(1, 0, 0));
		//view = glm::rotate(view,
			//glm::radians(windowManager->inputManager.getYaw()),
			//glm::vec3(0, 1, 0));
		glm::vec3 cameraPos = windowManager->inputManager.getCameraPos();
		glm::vec3 cameraLookAt = windowManager->inputManager.getCameraPos()
			+ windowManager->inputManager.getCameraDirection();
		//view = glm::translate(view,
			//glm::vec3(-cameraPos.x, -cameraPos.y, -cameraPos.z));
		view = glm::lookAt(cameraPos, cameraLookAt,
			glm::vec3(0, 1, 0));



		//view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
		projection = glm::perspective(45.0f,
				(GLfloat) WindowManager::screenWidth
						/ (GLfloat) WindowManager::screenHeight, 0.1f, 100.0f);
		// Get their uniform location
		shader.getUniformLocation("model");
		GLint modelLoc = shader.getUniformLocation("model");
		GLint viewLoc = shader.getUniformLocation("view");
		GLint projLoc = shader.getUniformLocation("projection");
		// Pass the matrices to the shader
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		// Note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		for (GLuint i = 0; i < 2; i++){
			glm::mat4 model;
			model = glm::translate(model, posicionObjeto[i]);
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
			if (i == 0){
				
				sphere.render();
			}
			else if(i==1){
				
				sphere.renderCube();
			}
		}
		//glm::mat4 model;
		//model = glm::translate(model, glm::vec3(0.0f,0.0f,-3.0f));
			/*Rotacion automática:
			glm::rotate(model, (GLfloat) timeValue * 1.0f, glm::vec3(0.0f, 1.0f, 0.0f));*/
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		//sphere.render();

		//glBindVertexArray(VAO);
		/*glDrawElements( GL_TRIANGLES, 36, GL_UNSIGNED_INT,
		 (GLvoid*) (sizeof(GLuint) * 0));*/
		//glBindVertexArray(0);
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
	
	sphere.deleteBuffers();
}
