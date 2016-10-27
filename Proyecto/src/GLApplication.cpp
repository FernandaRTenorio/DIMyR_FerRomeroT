/*
 * GLApplication.cpp
 *
 *  Created on: 07/08/2016
 *      Author: rey
 */

#include "Headers/GLApplication.h"
#include "Headers/Header.h"

Shader shader, shader2, shader3; //declaramos un shader
//shader2 es para pasarle la matriz de modelo, vista y proyeccion
//shader3 es para los modelos

/*Creacion de esferas*/
Sphere sphere(1.0, 25, 25, MODEL_MODE::VERTEX_LIGHT_TEXTURE);
Sphere sol(2.0, 25, 25, MODEL_MODE::VERTEX_LIGHT_TEXTURE);
Sphere cubo(10.0, 25, 25, MODEL_MODE::VERTEX_LIGHT_TEXTURE);

GLuint VAO, VBO, EBO, VAO2, VBO2, EBO2; //declaramos los buffers para vertices, e indices


//Declaracion de Texturas
Texture textureDifuse(GL_TEXTURE_2D, "Textures/container2.png");
Texture textureSpecular(GL_TEXTURE_2D, "Textures/container2_specular.png");
Texture texture(GL_TEXTURE_2D, "Textures/pasto.jpg");
Texture textureRobot(GL_TEXTURE_2D, "Textures/metal.jpg");
Texture texCroc(GL_TEXTURE_2D, "Textures/cocodrilo_skin01_512x512.jpg");
Texture textrex(GL_TEXTURE_2D, "Textures/Trex.jpg");
Texture texpump(GL_TEXTURE_2D, "Textures/HalloweenPumpkin_diff.tga");
Texture texbaymax(GL_TEXTURE_2D, "Textures/EyesWhite.jpg");
Texture texcaja1(GL_TEXTURE_2D,"Textures/cajamadera.jpg");
Texture texcaja2(GL_TEXTURE_2D,"Textures/cajametal.jpg");
Texture texsol(GL_TEXTURE_2D, "Textures/sol.jpg");

//Shader del Plano Horizontal
struct VertexColorTexture{
	glm::vec3 m_Pos;
	glm::vec3 m_Color;
	glm::vec2 m_TexCoord;
};

struct VertexTexture{
	glm::vec3 m_Pos;
	glm::vec2 m_TexCoord;
};


GLApplication::GLApplication() :
		windowManager(nullptr){
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
			|| !windowManager->initialize(800, 700, "Proyecto DIMyR", false)) {
		this->destroy();
		exit(-1);
	}

	glViewport(0, 0, WindowManager::screenWidth, WindowManager::screenHeight);
	glClearColor(0.2f, 0.2f, 0.2f, 0.0f);

	//glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	//aqui se inicializan los shaders
	/*Inicializando shader para el plano horizontal*/
	shader2.initialize("Shaders/sistemascoordenados.vs", "Shaders/sistemascoordenados.fs");
	shader3.initialize("Shaders/lightingSpecularMap.vs", "Shaders/LightingSpecularMap.fs");
	
	//Inicializacion de esferas
	sphere.init_para_sbb();
	sphere.load_sbb();
	cubo.init_para_sbb();

	sol.init();
	sol.load();

	//Dibujando el plano Horizontal
	VertexColorTexture vertices[4] = {
		{ glm::vec3(-1.8f, 0.0f, 0.9f), glm::vec3(0.2f, 0.2f, 0.2f), glm::vec2(0.0f,0.0f) },//0
		{ glm::vec3(1.8f, 0.0f, 0.9f), glm::vec3(0.2f, 0.2f, 0.2f), glm::vec2(1.0f, 0.0f) }, //1
		{ glm::vec3(1.8f, 0.0f, -0.9f), glm::vec3(0.2f, 0.2f, 0.2f), glm::vec2(1.0f, 1.0f) },
		{ glm::vec3(-1.8f, 0.0f, -0.9f), glm::vec3(0.2f, 0.2f, 0.2f), glm::vec2(0.0f, 1.0f) }
	};
	//Indices para dibujar el plano
	GLuint indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	/*Vertices para los dos cubos que se desplazan*/
	VertexTexture vert[36] = { { glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 0.0f) }, 
	{ glm::vec3(0.5f, -0.5f, -0.5f), glm::vec2(1.0f,0.0f) }, 
	{ glm::vec3(0.5f, 0.5f, -0.5f),  glm::vec2(1.0f, 1.0f) }, 
	{ glm::vec3(0.5f, 0.5f, -0.5f),  glm::vec2(1.0f, 1.0f) },
	{ glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec2(0.0f, 1.0f)}, 
	{ glm::vec3(-0.5f,-0.5f, -0.5f), glm::vec2(0.0f, 0.0f)},//TRASERA
	{ glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec2(0.0f, 0.0f)},
	{ glm::vec3(0.5f, -0.5f, 0.5f),  glm::vec2(1.0f, 0.0f) }, 
	{ glm::vec3(0.5f, 0.5f, 0.5f),   glm::vec2(1.0f, 1.0f) },
    { glm::vec3(0.5f, 0.5f, 0.5f),   glm::vec2(1.0f, 1.0f) }, 
	{ glm::vec3(-0.5f, 0.5f, 0.5f),  glm::vec2(0.0f, 1.0f) }, 
	{ glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec2(0.0f, 0.0f) },//FRONTAL
	{ glm::vec3(-0.5f, 0.5f, 0.5f),  glm::vec2(1.0f, 0.0f) }, 
	{ glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec2(1.0f, 1.0f) },
	{ glm::vec3(-0.5f, -0.5f, -0.5f),glm::vec2(0.0f, 1.0f) }, 
	{ glm::vec3(-0.5f, -0.5f, -0.5f),glm::vec2(0.0f, 1.0f) },
	{ glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec2(0.0f, 0.0f) },
	{ glm::vec3(-0.5f, 0.5f, 0.5f),  glm::vec2(1.0f, 0.0f) }, //IZQUIERDA
	{ glm::vec3(0.5f, 0.5f, 0.5f),   glm::vec2(1.0f, 0.0f) },
	{ glm::vec3(0.5f, 0.5f, -0.5f),  glm::vec2(1.0f, 1.0f) }, 
	{ glm::vec3(0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 1.0f) },
	{ glm::vec3(0.5f, -0.5f, -0.5f), glm::vec2(0.0f, 1.0f) },
	{ glm::vec3(0.5f, -0.5f, 0.5f),  glm::vec2(0.0f, 0.0f) },
	{ glm::vec3(0.5f, 0.5f, 0.5f),   glm::vec2(1.0f, 0.0f) },//DERECHA
	{ glm::vec3(-0.5f, -0.5f, -0.5f),glm::vec2(0.0f, 1.0f) },
	{ glm::vec3(0.5f, -0.5f, -0.5f), glm::vec2(1.0f, 1.0f) },
	{ glm::vec3(0.5f, -0.5f, 0.5f),  glm::vec2(1.0f, 0.0f) },
	{ glm::vec3(0.5f, -0.5f, 0.5f),  glm::vec2(1.0f, 0.0f) },
	{ glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec2(0.0f, 0.0f) },
	{ glm::vec3(-0.5f, -0.5f, -0.5f),glm::vec2(0.0f, 1.0f) },//INFERIOR
	{ glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec2(0.0f, 1.0f) },
	{ glm::vec3(0.5f, 0.5f, -0.5f),  glm::vec2(1.0f, 1.0f) },
	{ glm::vec3(0.5f, 0.5f, 0.5f),   glm::vec2(1.0f, 0.0f) },
	{ glm::vec3(0.5f, 0.5f, 0.5f),   glm::vec2(1.0f, 0.0f) },
	{ glm::vec3(-0.5f, 0.5f, 0.5f),  glm::vec2(0.0f, 0.0f) },
	{ glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec2(0.0f, 1.0f) } };//SUPERIOR

	
	///""""""""""""""""""""""""""""""""""""""""Dibujar los dos cubos
	glGenVertexArrays(1, &VAO2);
	glGenBuffers(1, &VBO2);
	glGenBuffers(1, &EBO2);

	glBindVertexArray(VAO2);


	glBindBuffer(GL_ARRAY_BUFFER, VBO2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vert), vert, GL_STATIC_DRAW);
	
	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vert[0]),
		(GLvoid*)0);
	glEnableVertexAttribArray(0);
	
	// Texture Mapping attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vert[0]),
		(GLvoid*)(sizeof(vert[0].m_Pos)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO

	//"""""""""""""""""""""""""""""Vertices almacenados para el piso
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]),
		(GLvoid*)0);
	glEnableVertexAttribArray(0);
	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]),
		(GLvoid*) sizeof(vertices[0].m_Pos));
	glEnableVertexAttribArray(1);
	// Texture Mapping attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]),
		(GLvoid*)(sizeof(vertices[0].m_Color) + sizeof(vertices[0].m_Pos)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO


	//"""""""""""""""""""""""""""""""""""Cargamos texturas
	//textura para el piso de pasto
	texture.load();
	//difusa y especular para los modelos
	textureDifuse.load();
	textureSpecular.load();
	textureRobot.load();
	texCroc.load();
	textrex.load();
	texpump.load();
	texbaymax.load();
	texcaja1.load();
	texcaja2.load();
	texsol.load();

}

void GLApplication::applicationLoop() {
	bool processInput = true;

	//arreglo para posicionar los modelos
	glm::vec3 modelPositions[] =
	{
		glm::vec3(0.0f, -3.0f, 0.0f), //personaje robot
		glm::vec3(-2.0f, -3.0f, 5.0f),//cocodrilo
		glm::vec3(7.0f, -3.0f, 2.0f), //trex
		glm::vec3(-8.0, -3.0f, 20.0f),//pumpkin
		glm::vec3(6.0f,-3.0f,40.0f)//baymax
	};

	glm::vec3 scales[] = {
		glm::vec3(0.2f,0.2f,0.2f),//robot
		glm::vec3(0.15f, 0.15f, 0.15f),//cocodrilo
		glm::vec3(0.01f, 0.01f, 0.01f),//trex
		glm::vec3(0.1f, 0.1f, 0.1f),//pumpkin
		glm::vec3(0.1f,0.1f,0.1f)//baymax
	};

	GLfloat angulos[] = {
		0.0f,
		90.0f,
		180.0f,
		90.0f,
		0.0f
	
	};

	//Arreglo para posicionar los dos cubos
	glm::vec3 cubePositions[] = {
		glm::vec3(5.0f, -1.0f, 0.0f),
		glm::vec3(5.0f, 3.0f, 0.0f)
	};

	//variable de tiempo
	double lastTime = TimeManager::Instance().GetTime();

	//posiciones de luces
	glm::vec3 lightPos(0.0f,0.0f,8.0f); 
	

	//inicializacion de modelos
	Model objModel5("models/BaymaxWhiteOBJ/Bigmax_White_OBJ.obj");
	Model objModel4("models/HalloweenPumpkin_OBJ/Halloween_Pumpkin.obj");
	Model objModel3("models/trex/Trex.obj");
	Model objModel2("models/Cocodrilo/Cocodrilo.obj");
	Model objModel("models/robot/Robot.obj");

	
	//Obtenemos los SBB de cada modelo
	
	SBB sbb = getSBB(objModel.getMeshes());
	AABB aabb2 = getAABB(objModel2.getMeshes());
	SBB sbb2 = getSBB(objModel2.getMeshes());
	SBB sbb3 = getSBB(objModel3.getMeshes());
	SBB sbb4 = getSBB(objModel4.getMeshes());
	SBB sbb5 = getSBB(objModel5.getMeshes());

	
	while (processInput) {
		processInput = windowManager->processInput(true);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.2f,0.3f,0.3f,1.0f);


		//Variable de tiempo que vamos a ocupar para hacer cambios
		GLfloat timeValue = TimeManager::Instance().GetTime() - lastTime;

		/*Transformaciones para la camara de tercera persona*/
		glm::mat4 view;
		view = glm::rotate(view, glm::radians(windowManager->inputManager.getPitch()), glm::vec3(1, 0, 0));
		view = glm::rotate(view, glm::radians(windowManager->inputManager.getYaw()), glm::vec3(0, 1, 0));
		glm::vec3 cameraPos = windowManager->inputManager.getCameraPos();
		view = glm::translate(view, glm::vec3(-cameraPos.x, -cameraPos.y, -cameraPos.z));
		glm::mat4 projection;
		projection = glm::perspective(45.0f, (GLfloat)WindowManager::screenWidth / (GLfloat)WindowManager::screenHeight, 0.1f, 100.0f);


		//UTILIZACION DE SHADERS
		/*""""""""""""""""""""""""""""""SHADER 2 PARA EL PLANO DE PASTO"""""""""""""""""""""""""""""""*/
		shader2.turnOn();
		//Bindeamos las texturas
		
		/*conseguimos la localizacion de las variables uniform del shader*/
		shader2.getUniformLocation("model");
		GLint modelLoc = shader2.getUniformLocation("model");
		GLint viewLoc = shader2.getUniformLocation("view");
		GLint projLoc = shader2.getUniformLocation("projection");

		/*Pasamos datos a shaders*/
		// Pass the matrices to the shader
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		// Note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		/*Dibujado de elementos*/


		texsol.bind(GL_TEXTURE0);
		glm::mat4 psol;
		GLfloat radius = 30.0f;
		GLfloat solX = sin((GLfloat)timeValue * 1.0f) * radius;
		GLfloat solY = cos((GLfloat)timeValue * 1.0f) * radius;

		psol = glm::translate(psol, glm::vec3(solX, solY, 0.0f));
		//psol = glm::scale(psol, glm::vec3(2.5f, 1.0f, 4.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(psol));
		sol.render2();

		texture.bind(GL_TEXTURE0);
		//dibujamos el plano
		glBindVertexArray(VAO);
		glm::mat4 model;
		model = glm::translate(model, glm::vec3(0.0f, -2.5f, 1.0f));
		model = glm::scale(model, glm::vec3(2.5f, 1.0f, 4.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		//Dibujamos los cubos
		
		glBindVertexArray(VAO2);
		for (GLuint i = 0; i < 2; i++){
			glm::mat4 modelcubo;
			modelcubo = glm::translate(modelcubo, cubePositions[i]);
			//modelcubo = glm::rotate(modelcubo, 180.0f, glm::vec3(0.0f, 1.0f, 0.0f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelcubo));
			if (i == 0){
				texcaja1.bind(GL_TEXTURE0);
				glDrawArrays(GL_TRIANGLES, 0, 36);
			}
			else{
				texcaja2.bind(GL_TEXTURE0);
				glDrawArrays(GL_TRIANGLES, 0, 36);
			}
		
		}

		//apagamos el shader 
		shader2.turnOff();

		/*""""""""""""""""""""""""""""""SHADER 3 PARA EL PERSONAJE Y MODELOS""""""""""""""""""""""""""""""*/
		shader3.turnOn();

		//Caracteristicas de los modelos
		GLint viewPosLoc = shader3.getUniformLocation("viewPos");
		glm::vec3 cameraPos2 = windowManager->inputManager.getCameraPos();
		glUniform3f(viewPosLoc, -cameraPos2.x, -cameraPos2.y,-cameraPos2.z);

		//Propiedades de los materiales
		GLint matDiffuseLoc = shader3.getUniformLocation("material.diffuse");
		GLint matSpecularLoc = shader3.getUniformLocation("material.specular");
		GLint matShineLoc = shader3.getUniformLocation("material.shininess");
		glUniform1i(matDiffuseLoc, 0);
		glUniform1i(matSpecularLoc, 1);
		glUniform1f(matShineLoc, 32.0f);

		//Propiedades de las luces
		GLint lightAmbientLoc = shader3.getUniformLocation("light.ambient");
		GLint lightDiffuseLoc = shader3.getUniformLocation("light.diffuse");
		GLint lightSpecularLoc = shader3.getUniformLocation("light.specular");
		GLint lightPosLoc = shader3.getUniformLocation("light.position");
		glUniform3f(lightAmbientLoc, 0.2f, 0.2f, 0.2f);
		glUniform3f(lightDiffuseLoc, 0.5f, 0.5f, 0.5f); 
		glUniform3f(lightSpecularLoc, 1.0f, 1.0f, 1.0f);
		glUniform3f(lightPosLoc, lightPos.x, lightPos.y, lightPos.z);

		//dibujamos el modelo cargado
		// Get the uniform locations
		GLint modelLoc2 = shader3.getUniformLocation("model");
		GLint viewLoc2 = shader3.getUniformLocation("view");
		GLint projLoc2 = shader3.getUniformLocation("projection");
		// Pass the matrices to the shader
		glUniformMatrix4fv(viewLoc2, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc2, 1, GL_FALSE, glm::value_ptr(projection));
		
		for (int i = 0; i < 5; i++){
			glm::mat4 model2;
			model2 = glm::translate(model2, modelPositions[i]);
			model2 = glm::scale(model2, scales[i]);
			model2 = glm::rotate(model2, angulos[i], glm::vec3(0.0f, 1.0f, 0.0f));
			glUniformMatrix4fv(modelLoc2, 1, GL_FALSE, glm::value_ptr(model2));
			if (i == 0){
				//texturas
				textureRobot.bind(GL_TEXTURE0);
				model2 = glm::translate(model2, windowManager->inputManager.getCharacterPosition());
				model2 = glm::rotate(model2, windowManager->inputManager.getCharacterRotation(), glm::vec3(0.0f, 1.0f, 0.0f));
				glUniformMatrix4fv(modelLoc2, 1, GL_FALSE, glm::value_ptr(model2));
				objModel.render(&shader3);

				model2 = glm::translate(model2,
					glm::vec3(sbb.center.x, sbb.center.y, sbb.center.z));
				model2 = glm::scale(model2,
					glm::vec3(sbb.ratio, sbb.ratio, sbb.ratio));
				glUniformMatrix4fv(modelLoc2, 1, GL_FALSE, glm::value_ptr(model2));
				sphere.render();
				

			}
			else if (i == 1){
				//texturas
				texCroc.bind(GL_TEXTURE0);
				objModel2.render(&shader3);

				model2 = glm::translate(model2, aabb2.center);
					//glm::vec3(sbb2.center.x, sbb2.center.y, sbb2.center.z));
				
				model2 = glm::scale(model2, glm::vec3(5.0f,5.0f,5.0f));
					//glm::vec3(sbb2.ratio,sbb2.ratio,sbb2.ratio));
				//aabb2.dist, aabb2.dist, aabb2.dist
				glUniformMatrix4fv(modelLoc2, 1, GL_FALSE, glm::value_ptr(model2));
				//sphere.render();
				cubo.loadCube(aabb2);
				cubo.renderCube();
			}
			else if (i == 2){
				textrex.bind(GL_TEXTURE0);
				objModel3.render(&shader3);

				model2 = glm::translate(model2,
					glm::vec3(sbb3.center.x, sbb3.center.y, sbb3.center.z));
				model2 = glm::scale(model2,
					glm::vec3(sbb3.ratio, sbb3.ratio, sbb3.ratio));
				glUniformMatrix4fv(modelLoc2, 1, GL_FALSE, glm::value_ptr(model2));
				sphere.render();


			}
			else if (i == 3){
				texpump.bind(GL_TEXTURE0);
				objModel4.render(&shader3);

				model2 = glm::translate(model2,
					glm::vec3(sbb4.center.x, sbb4.center.y, sbb4.center.z));
				model2 = glm::scale(model2,
					glm::vec3(sbb4.ratio, sbb4.ratio, sbb4.ratio));
				glUniformMatrix4fv(modelLoc2, 1, GL_FALSE, glm::value_ptr(model2));
				sphere.render();

			}
			else if (i == 4){
				texbaymax.bind(GL_TEXTURE0);
				objModel5.render(&shader3);
				
				model2 = glm::translate(model2,
					glm::vec3(sbb5.center.x, sbb5.center.y, sbb5.center.z));
				model2 = glm::scale(model2,
					glm::vec3(sbb5.ratio, sbb5.ratio, sbb5.ratio));
				glUniformMatrix4fv(modelLoc2, 1, GL_FALSE, glm::value_ptr(model2));
				sphere.render();
			}
			SBB s1, s2;
			s1.center = glm::vec3(model2* glm::vec4(0, 0, 0, 1));
			s1.ratio = sbb.ratio *0.2f;
			s2.center = glm::vec3(model2*glm::vec4(0, 0, 0, 1));
			s2.ratio = sbb2.ratio * 0.01f;
			bool colision = false;
			colision = SBBvsSBB(s1, s2);

			if (colision){
				windowManager->inputManager.setCharacterPosition(colision);
				std::cout << "colision!!:" << colision << std::endl;
				colision = false;

			}
		}
		

		//Apagamos el shader
		shader3.turnOff();

		glClearColor(0.2f,0.3f,0.3f,1.0f); // color de fondo de pantalla
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
