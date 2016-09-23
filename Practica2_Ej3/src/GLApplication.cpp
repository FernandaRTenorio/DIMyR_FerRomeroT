/*
 * GLApplication.cpp
 *
 *  Created on: 07/08/2016
 *      Author: rey
 */

#include "Headers/GLApplication.h"
Sphere sp(10.0f, 50, 50, MODEL_MODE::VERTEX_COLOR);
Sphere sp2(1.5, 50, 50, MODEL_MODE::VERTEX_LIGHT_TEXTURE);
Shader shader;
Shader lampShader;
Shader lightingShader;

Texture textureDifuse(GL_TEXTURE_2D, "Textures/container2.png");
Texture textureSpecular(GL_TEXTURE_2D, "Textures/container2_specular.png");

GLuint VAO, VBO, EBO;

GLApplication::GLApplication() :
		windowManager(nullptr), camera(nullptr) {
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
	glClearColor(0.2f, 0.2f, 0.2f, 0.0f);

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	sp.init();
	sp.load();

	//sp2.init();
	//sp2.load();
	textureDifuse.load();
	textureSpecular.load();

	lightingShader.initialize("Shaders/lightingSpecularMap.vs",
		"Shaders/lightingSpecularMap.fs");
	lampShader.initialize("Shaders/lampShader.vs", "Shaders/lampShader.fs");

	shader.initialize("Shaders/shader.vs", "Shaders/shader.fs");

}
void GLApplication::applicationLoop() {
	bool processInput = true;
	double lastTime = TimeManager::Instance().GetTime();
	glm::vec3 lightPos(4.5f, 7.0f, -3.0f);
	//Model objModel("objects/baymax/Bigmax_White_OBJ.obj");
	
	Model objModel("objects/S104-C_OBJ/S104-C.obj");
	//Model objModel2("objects/Tree_Dry_1_Obj/Tree_Dry_1_LOD1.obj");
	Model objModel2("objects/S104-C_OBJ/S104-C.obj");
	
	//Model objModel2("objects/S104-C_OBJ/S104-C.obj");

	while (processInput) {
		processInput = windowManager->processInput(true);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		GLfloat timeValue = TimeManager::Instance().GetTime() - lastTime;

		//shader.turnOn();
		lightingShader.turnOn();
		GLint viewPosLoc = lightingShader.getUniformLocation("viewPos");
		glUniform3f(viewPosLoc, camera->Position.x, camera->Position.y, camera->Position.z);
		
		GLfloat radius = 20.0f;

		GLfloat posX = sin((GLfloat)timeValue * 1.0f) * radius;
		GLfloat posZ = cos((GLfloat)timeValue * 1.0f) * radius;

		// Set material properties
		GLint matDiffuseLoc = lightingShader.getUniformLocation(
			"material.diffuse");
		GLint matSpecularLoc = lightingShader.getUniformLocation(
			"material.specular");
		GLint matShineLoc = lightingShader.getUniformLocation(
			"material.shininess");
		glUniform1i(matDiffuseLoc, 0);
		glUniform1i(matSpecularLoc, 1);
		glUniform1f(matShineLoc, 32.0f);

		// Set lights properties
		GLint lightAmbientLoc = lightingShader.getUniformLocation(
			"light.ambient");
		GLint lightDiffuseLoc = lightingShader.getUniformLocation(
			"light.diffuse");
		GLint lightSpecularLoc = lightingShader.getUniformLocation(
			"light.specular");
		lightPos = glm::vec3(posX,4.0f,posZ);
		GLint lightPosLoc = lightingShader.getUniformLocation("light.position");
		glUniform3f(lightAmbientLoc, 0.2f, 0.2f, 0.2f);
		glUniform3f(lightDiffuseLoc, 0.5f, 0.5f, 0.5f); // Let's darken the light a bit to fit the scene
		glUniform3f(lightSpecularLoc, 1.0f, 1.0f, 1.0f);
		glUniform3f(lightPosLoc, lightPos.x, lightPos.y, lightPos.z);

		
		
		// Transformation matrices
		glm::mat4 view = camera->GetViewMatrix();
		glm::mat4 projection;
		projection = glm::perspective(45.0f,
				(GLfloat) WindowManager::screenWidth
						/ (GLfloat) WindowManager::screenHeight, 0.1f, 100.0f);
		// Get the uniform locations
		GLint modelLoc = lightingShader.getUniformLocation("model");
		//GLint modelLoc2 = shader.getUniformLocation("model2");
		GLint viewLoc = lightingShader.getUniformLocation("view");
		GLint projLoc = lightingShader.getUniformLocation("projection");
		// Pass the matrices to the shader
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		//Dibujando el primer modelo
		glm::mat4 model;
		model = glm::translate(model, glm::vec3(-5.0f, -1.75f, -3.0f));
		model = glm::rotate(model, 160.0f, glm::vec3(0.0f,0.0f,1.0f));
		
		model = glm::scale(model, glm::vec3(0.05f, 0.05f, 0.05f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		objModel.render(&shader);

		//Dibujando el segundo modelo
		glm::mat4 model2;
		model2 = glm::translate(model2, glm::vec3(5.5f, -1.75f, -3.0f));
		model2 = glm::rotate(model2, -90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		model2 = glm::rotate(model2, 90.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		model2 = glm::scale(model2, glm::vec3(0.08f, 0.08f, 0.08f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model2));
		objModel2.render(&shader);

		lightingShader.turnOff();
		//shader.turnOff();

		//Dibujando la lampara
		lampShader.turnOn();
		// Create transformations
		modelLoc = lampShader.getUniformLocation("model");
		viewLoc = lampShader.getUniformLocation("view");
		projLoc = lampShader.getUniformLocation("projection");
		// Pass the matrices to the shader
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		model = glm::scale(glm::mat4(), glm::vec3(0.5, 0.5, 0.5));
		model = glm::translate(model, glm::vec3(posX, 4.0f,posZ));
		model = glm::scale(model, glm::vec3(0.2, 0.2, 0.2));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		sp.render();
		lampShader.turnOff();


		windowManager->swapTheBuffers();
	}
}

void GLApplication::destroy() {
	if (windowManager) {
		delete windowManager;
		windowManager = nullptr;
	}

	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &VBO);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glDeleteBuffers(1, &EBO);

	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VAO);

}
