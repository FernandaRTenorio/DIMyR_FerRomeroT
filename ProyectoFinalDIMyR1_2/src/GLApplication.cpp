/*
 * GLApplication.cpp
 *
 *  Created on: 07/08/2016
 *  
 */

#include "Headers/GLApplication.h"
#include "Headers/collision.h"

GLuint VAO, VBO, EBO;

Cube cubo(1.0f, 1.0f, 1.0f, true);
Sphere esferaColision(1.0, 20, 20, true);
Sphere esfera(20.0, 25, 25, false);

Shader lampShader;
Shader shader;
Shader lighting;
Shader shaderSelection;

//Audio Components
#define NUM_BUFFERS 5
#define NUM_SOURCES 5
#define NUM_ENVIRONMENTS 1

/*ALfloat listenerPos[] = { 0.0, 0.0, 4.0 };
ALfloat listenerVel[] = { 0.0, 0.0, 0.0 };
ALfloat listenerOri[] = { 0.0, 0.0, 1.0, 0.0, 1.0, 0.0 };

//Audio
ALfloat source0Pos_robot[] = { 0.0f,0.0f,0.0f };
ALfloat source1Pos_croc[] = { 20.0f, 0.0f, -20.0f };
ALfloat source2Pos_trex[] = { -20.0f, 0.0f, 0.0f};
ALfloat source3Pos_pumpkin[] = { -5.0f, 0.0f, -20.0f };
ALfloat source4Pos_baymax[] = { 20.0f, 15.0f, -20.0f};


ALfloat source2Vel_trex[] = { 0.0, 0.0, 0.0 };
ALfloat source1Vel_croc[] = { 0.0, 0.0, 0.0 };
ALfloat source0Vel_robot[] = { 0.0, 0.0, 0.0 };
ALfloat source3Vel_pumpkin[] = { 0.0, 0.0, 0.0 };
ALfloat source4Vel_baymax[] = { 0.0, 0.0, 0.0 };

ALuint buffer[NUM_BUFFERS];
ALuint source[NUM_SOURCES];
ALuint environment[NUM_ENVIRONMENTS];

ALsizei size, freq;
ALenum format;
ALvoid *data;
int ch;
ALboolean loop;
*/

GLuint VAOpiso, VBOpiso, EBOpiso;


//Rayo para colision 
bool Colision::colisionCroc;
bool Colision::colisionTrex;
bool Colision::colisionPumpkin;
bool Colision::bajarCaja;


//Declaracion de Texturas
//Texture textureDifuse(GL_TEXTURE_2D, "Textures/container2.png");
Texture textureSpecular(GL_TEXTURE_2D, "Textures/container2_specular.png");
//Texture texture(GL_TEXTURE_2D, "Textures/pasto.jpg");
Texture textureRobot(GL_TEXTURE_2D, "Textures/metal.bmp");
Texture texCroc(GL_TEXTURE_2D, "Textures/cocodrilo_skin01_512x512.jpg");
Texture textrex(GL_TEXTURE_2D, "Textures/Trex.jpg");
Texture texpump(GL_TEXTURE_2D, "Textures/HalloweenPumpkin_diff.tga");
Texture texbaymax(GL_TEXTURE_2D, "Textures/EyesWhite.jpg");
//Texture texcaja1(GL_TEXTURE_2D, "Textures/cajamadera.jpg");
//Texture texcaja2(GL_TEXTURE_2D, "Textures/cajametal.jpg");
Texture texsol(GL_TEXTURE_2D, "Textures/sol.jpg");
Texture texturaSol(GL_TEXTURE_2D, "Textures/sol.jpg");
Texture texturaPiso(GL_TEXTURE_2D, "Textures/piso.jpg");
//Texture texCubo1(GL_TEXTURE_2D, "Textures/caja.jpg");

std::vector<GLuint> rays;

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
	if (!windowManager || !windowManager->initialize(800, 700, "Proyecto DIMYR", false)) {
		this->destroy();
		exit(-1);
	}

	glViewport(0, 0, WindowManager::screenWidth, WindowManager::screenHeight);
	glClearColor(0.2f, 0.2f, 0.2f, 0.0f);

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	

	//Esfera Colision
	esferaColision.init();
	esferaColision.load();

	//Cubo Colision 
	cubo.init();
	cubo.load();

	//Esfera sol
	esfera.init();
	esfera.load();

	Colision::bajarCaja = false;

	//Audio
	/*
	alutInit(0, NULL);

	alListenerfv(AL_POSITION, listenerPos);
	alListenerfv(AL_VELOCITY, listenerVel);
	alListenerfv(AL_ORIENTATION, listenerOri);

	alGetError(); // clear any error messages

	if (alGetError() != AL_NO_ERROR) {
		printf("- Error creating buffers !!\n");
		exit(1);
	}
	else {
		printf("init() - No errors yet.");
	}

	// Generate buffers, or else no sound will happen!
	alGenBuffers(NUM_BUFFERS, buffer);

	buffer[0] = alutCreateBufferFromFile("sounds/robot.wav");
	buffer[1] = alutCreateBufferFromFile("sounds/croc.wav");
	buffer[2] = alutCreateBufferFromFile("sounds/dino.wav");
	buffer[3] = alutCreateBufferFromFile("sounds/pumpkin.wav");
	buffer[4] = alutCreateBufferFromFile("sounds/baymax.wav");
	

	alGetError(); 
	alGenSources(NUM_SOURCES, source);

	if (alGetError() != AL_NO_ERROR) {
		printf("- Error creating sources !!\n");
		exit(2);
	}
	else {
		printf("init - no errors after alGenSources\n");
	}

	alSourcef(source[0], AL_PITCH, 1.0f);
	alSourcef(source[0], AL_GAIN, 1.0f);
	alSourcefv(source[0], AL_POSITION, source0Pos_robot);
	alSourcefv(source[0], AL_VELOCITY, source0Vel_robot);
	alSourcei(source[0], AL_BUFFER, buffer[0]);
	alSourcei(source[0], AL_LOOPING, AL_TRUE);
	alSourcef(source[0], AL_MAX_DISTANCE, 1200);

	alSourcef(source[1], AL_PITCH, 1.0f);
	alSourcef(source[1], AL_GAIN, 1.0f);
	alSourcefv(source[1], AL_POSITION, source1Pos_croc);
	alSourcefv(source[1], AL_VELOCITY, source1Vel_croc);
	alSourcei(source[1], AL_BUFFER, buffer[1]);
	alSourcei(source[1], AL_LOOPING, AL_TRUE);

	alSourcef(source[2], AL_PITCH, 1.0f);
	alSourcef(source[2], AL_GAIN, 1.0f);
	alSourcefv(source[2], AL_POSITION, source2Pos_trex);
	alSourcefv(source[2], AL_VELOCITY, source2Vel_trex);
	alSourcei(source[2], AL_BUFFER, buffer[2]);
	alSourcei(source[2], AL_LOOPING, AL_TRUE);

	alSourcef(source[3], AL_PITCH, 1.0f);
	alSourcef(source[3], AL_GAIN, 1.0f);
	alSourcefv(source[3], AL_POSITION, source3Pos_pumpkin);
	alSourcefv(source[3], AL_VELOCITY, source3Vel_pumpkin);
	alSourcei(source[3], AL_BUFFER, buffer[3]);
	alSourcei(source[3], AL_LOOPING, AL_TRUE);

	alSourcef(source[4], AL_PITCH, 1.0f);
	alSourcef(source[4], AL_GAIN, 1.0f);
	alSourcefv(source[4], AL_POSITION, source4Pos_baymax);
	alSourcefv(source[4], AL_VELOCITY, source4Vel_baymax);
	alSourcei(source[4], AL_BUFFER, buffer[4]);
	alSourcei(source[4], AL_LOOPING, AL_TRUE);
	*/

	//inicializar piso

	VertexNormalText verticesPiso[4] =
	{
		{
			glm::vec3(1, 0, 1),
			glm::vec3(0, 1, 0),
			glm::vec2(10, 0)
		},
		{
			glm::vec3(1, 0, -1),
			glm::vec3(0, 1, 0),
			glm::vec2(10, 10)
		},
		{
			glm::vec3(-1, 0, -1),
			glm::vec3(0, 1, 0),
			glm::vec2(0, 10)
		},
		{
			glm::vec3(-1, 0, 1),
			glm::vec3(0, 1, 0),
			glm::vec2(0, 0)
		}
	};

	GLuint indices[6] = 
	{ 0, 1, 3, 
	1, 2, 3 };

	glGenVertexArrays(1, &VAOpiso);
	glGenBuffers(1, &VBOpiso);
	glGenBuffers(1, &EBOpiso);

	glBindVertexArray(VAOpiso);

	glBindBuffer(GL_ARRAY_BUFFER, VBOpiso);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticesPiso), verticesPiso, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOpiso);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
		GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(verticesPiso[0]),
		(GLvoid*)0);
	glEnableVertexAttribArray(0);
	// Normal attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(verticesPiso[0]),
		(GLvoid*) sizeof(verticesPiso[0].position));
	glEnableVertexAttribArray(1);
	// Texture attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(verticesPiso[0]),
		(GLvoid*)(sizeof(verticesPiso[0].position) + sizeof(verticesPiso[0].normal)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO

	//"""""""""""""""""""""""""""""""""""Cargamos texturas
	//textura para el piso de pasto
	//texture.load();
	//difusa y especular para los modelos
	//textureDifuse.load();
	textureSpecular.load();
	textureRobot.load();
	texCroc.load();
	textrex.load();
	texpump.load();
	texbaymax.load();
	//texcaja1.load();
	//texcaja2.load();
	texsol.load();
	//texCubo1.load();
	texturaSol.load();
	texturaPiso.load();

	
	lighting.initialize("Shaders/lightingSpecularMap.vs", "Shaders/lightingSpecularMap.fs");
	lampShader.initialize("Shaders/lampShader.vs", "Shaders/lampShader.fs");
	shader.initialize("Shaders/shader.vs", "Shaders/shader.fs");
	/*shaderSelection.initialize("Shaders/selectionShader.vs",
		"Shaders/selectionShader.fs");*/
}

void GLApplication::applicationLoop() {
	bool processInput = true;
	glm::vec3 lightPos( 0.0f, 0.0f, 0.0f);

	
	//Posicion de modelos
	glm::vec3 robotPos(0.0f,0.0f,0.0f);
	glm::vec3 crocPos(20.0f, 0.0f, -20.0f);//croc
	glm::vec3 trexPos(-20.0f, 0.0f, 0.0f); //trex
	glm::vec3 pumpkinPos(-5.0f, 0.0f, -20.0f);//pumpkin
	glm::vec3 baymaxPos(20.0f, 15.0f, -20.0f);//baymax

	Model baymaxModel("models/BaymaxWhiteOBJ/Bigmax_White_OBJ.obj");
	Model pumpkinModel("models/HalloweenPumpkin_OBJ/Halloween_Pumpkin.obj");
	Model trexModel("models/trex/Trex.obj");
	Model crocModel("models/Cocodrilo/Cocodrilo.obj");
	Model robotModel("models/robot/Robot.fbx");

	//Audio
	/*ALfloat source0Pos_robot[] = { robotPos.x, robotPos.y, robotPos.z };
	ALfloat source1Pos_croc[] = { crocPos.x, crocPos.y, crocPos.z };
	ALfloat source2Pos_trex[] = { trexPos.x,trexPos.y,trexPos.z };
	ALfloat source3Pos_pumpkin[] = { pumpkinPos.x, pumpkinPos.y, pumpkinPos.z };
	ALfloat source4Pos_baymax[] = { baymaxPos.x, baymaxPos.y, baymaxPos.z };
	*/

	//Definir volumenes envolventes al modelo
	SBB sbb1 = getSBB(robotModel.getMeshes());
	SBB sbb2 = getSBB(pumpkinModel.getMeshes());
	AABB aabb1 = getAABB(crocModel.getMeshes());
	AABB aabb2 = getAABB(trexModel.getMeshes());
	AABB aabb3 = getAABB(baymaxModel.getMeshes());

	float angRobot = 0.0f;
	float angCroc = 0.0f;
	float angTrex = 0.0f;
	float angPumpkin = 0.0f;
	float angBaymax = 0.0f;

	double lastTime = TimeManager::Instance().GetTime();

	while (processInput) {
		processInput = windowManager->processInput(true);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::vec4 viewport = glm::vec4(0.0f, 0.0f, WindowManager::screenWidth,
			WindowManager::screenHeight);
		glClearColor(0.6f, 0.6f, 0.9f, 1.0f);

		//Rotar esfera de luz
		GLfloat timeValue = TimeManager::Instance().GetTime() - lastTime;
		GLfloat valX = sin((GLfloat)timeValue * 1.0f) * 70.0f;
		GLfloat valY = sin((GLfloat)timeValue * 3.1416f / 2) * 70.0f;
		//GLfloat valZ = cos((GLfloat)timeValue * 1.0f) * 70.0f;
		lightPos.x = valX;
		lightPos.y = valY;
		//lightPos.z = valZ;

		lighting.turnOn();

		GLint viewPosLoc = lighting.getUniformLocation("viewPos");
		glUniform3f(viewPosLoc, camera->CamPosition.x, camera->CamPosition.y, camera->CamPosition.z);

		// Set material properties
		GLint matShineLoc = lighting.getUniformLocation("material.shininess");
		glUniform1f(matShineLoc, 10.0f);//50.0f

		// Set lights properties
		GLint lightAmbientLoc = lighting.getUniformLocation("light.ambient");
		GLint lightDiffuseLoc = lighting.getUniformLocation("light.diffuse");
		GLint lightSpecularLoc = lighting.getUniformLocation("light.specular");
		GLint lightPosLoc = lighting.getUniformLocation("light.position");
		glUniform3f(lightAmbientLoc, 0.2f, 0.2f, 0.2f);
		glUniform3f(lightDiffuseLoc, 0.5f, 0.5f, 0.5f); // Let's darken the light a bit to fit the scene
		glUniform3f(lightSpecularLoc, 1.0f, 1.0f, 1.0f);
		glUniform3f(lightPosLoc, lightPos.x, lightPos.y, lightPos.z);

		// Transformation matrices
		glm::mat4 view = camera->GetViewMatrix();
		glm::mat4 projection;
		projection = glm::perspective(45.0f, (GLfloat)WindowManager::screenWidth / (GLfloat)WindowManager::screenHeight, 0.1f, 100.0f);
		// Get the uniform locations
		GLint modelLoc = lighting.getUniformLocation("model");
		GLint viewLoc = lighting.getUniformLocation("view");
		GLint projLoc = lighting.getUniformLocation("projection");
		// Pass the matrices to the shader
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));


		// Draw the loaded model
		glm::mat4 model;

		//ROBOT
		robotPos = glm::vec3(camera->CharPosition.x, camera->CharPosition.y, camera->CharPosition.z);

		glm::mat4 modelRobot;
		modelRobot = glm::translate(modelRobot, robotPos);
		modelRobot = glm::rotate(modelRobot, (GLfloat)glm::radians(180.0f + angRobot - camera->angleAroundPlayer), glm::vec3(0.0f, 1.0f, 0.0f));
		modelRobot = glm::scale(modelRobot, glm::vec3(0.5f, 0.5f, 0.5f));
		textureRobot.bind(GL_TEXTURE0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelRobot));
		robotModel.render(&lighting);

		//CROCODILE
		glm::mat4 modelCroc;
		modelCroc = glm::translate(modelCroc, crocPos);
		modelCroc = glm::rotate(modelCroc, (GLfloat)glm::radians(angCroc), glm::vec3(0.0f, 1.0f, 0.0f));
		modelCroc = glm::scale(modelCroc, glm::vec3(0.5f,0.5f,0.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelCroc));
		texCroc.bind(GL_TEXTURE0);
		crocModel.render(&lighting);

		//TREX
		glm::mat4 modelTrex;//trex
		modelTrex = glm::translate(modelTrex, trexPos);
		modelTrex = glm::rotate(modelTrex, (GLfloat)glm::radians(angTrex), glm::vec3(0.0f, 1.0f, 0.0f));
		modelTrex = glm::scale(modelTrex, glm::vec3(0.05f,0.05f,0.05f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelTrex));
		textrex.bind(GL_TEXTURE0);
		trexModel.render(&lighting);
	
		// Draw the loaded model3
		glm::mat4 modelPumpkin;//pumpkin
		modelPumpkin = glm::translate(modelPumpkin, pumpkinPos);
		modelPumpkin = glm::rotate(modelPumpkin, (GLfloat)glm::radians(angPumpkin), glm::vec3(0.0f, 1.0f, 0.0f));
		modelPumpkin = glm::scale(modelPumpkin, glm::vec3(0.3f, 0.3f, 0.3f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelPumpkin));
		texpump.bind(GL_TEXTURE0);
		pumpkinModel.render(&lighting);

		// Draw the loaded model4
		glm::mat4 modelBaymax;//baymax
		modelBaymax = glm::translate(modelBaymax, baymaxPos);
		modelBaymax = glm::rotate(modelBaymax, (GLfloat)glm::radians(angBaymax), glm::vec3(0.0f, 1.0f, 0.0f));
		modelBaymax= glm::scale(modelBaymax, glm::vec3(0.1f,0.1f,0.1f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelBaymax));
		texbaymax.bind(GL_TEXTURE0);
		baymaxModel.render(&lighting);
		
		/*DIBUJO ESCENARIO*/

		/*Piso*/
		model = glm::scale(glm::mat4(), glm::vec3(40.0, 40.0, 40.0));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		GLint unitTextureLocation = shader.getUniformLocation("material.texture_diffuse1");
		unitTextureLocation = shader.getUniformLocation("material.texture_specular1");
		glUniform1i(unitTextureLocation, 0);
		texturaPiso.bind(GL_TEXTURE0);
		glBindVertexArray(VAOpiso);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (GLvoid*)(sizeof(GLuint) * 0));
		glBindVertexArray(0);

		lighting.turnOff();
		
		/*Dibujo Sol*/
		lampShader.turnOn();

		// Create transformations
		modelLoc = lampShader.getUniformLocation("model");
		viewLoc = lampShader.getUniformLocation("view");
		projLoc = lampShader.getUniformLocation("projection");
		// Pass the matrices to the shader
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		model = glm::scale(glm::mat4(), glm::vec3(0.5, 0.5, 0.5));
		model = glm::translate(model, lightPos);
		model = glm::scale(model, glm::vec3(0.2, 0.2, 0.2));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

		texturaSol.bind(GL_TEXTURE0);
		glUniform1i(lampShader.getUniformLocation("ourTexture"), 0);
		texsol.bind(GL_TEXTURE0);
		esfera.render();
		lampShader.turnOff();

		/*FIN DIBUJA ESCENARIO*/

		/*Intento de Picking por Color*/
	/*	shaderSelection.turnOn();
		// Get the uniform locations
		modelLoc = shaderSelection.getUniformLocation("model");
		viewLoc = shaderSelection.getUniformLocation("view");
		projLoc = shaderSelection.getUniformLocation("projection");
		// Pass the matrices to the shader
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		model_play = glm::translate(model_play, robotPos);
		model_play = glm::rotate(model_play, (GLfloat)glm::radians(180.0f + angplay - camera->angleAroundPlayer), glm::vec3(0.0f, 1.0f, 0.0f));
		//model = glm::rotate(model, (GLfloat) 3.1416f, glm::vec3(0.0f, 1.0f, 0.0f));
		//model_play = glm::scale(model_play, glm::vec3(0.5f, 0.5f, 0.5f));
		textureRobot.bind(GL_TEXTURE0);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model_play));
		GLint codeLoc = shaderSelection.getUniformLocation("code");
		glUniform1i(codeLoc, 1);

		objModel_Player.render(&shaderSelection);

		shaderSelection.turnOff();
		
		if (windowManager->inputManager.isReadPixelBuffer()) {
			std::cout << "Read pixel buffer:" << std::endl;
			unsigned char res[4];
			glReadPixels(windowManager->inputManager.getLastMousePos().x,
				WindowManager::screenHeight
				- windowManager->inputManager.getLastMousePos().y,
				1, 1, GL_RGB, GL_UNSIGNED_BYTE, res);
			switch (res[0]) {
			case 0:
				std::cout << "Nothing" << std::endl;
				printf("Nothing Picked \n");
				break;
			case 1:
				printf("Picked Robot\n");
				break;
			case 2:
				printf("Picked cyborg\n");
				break;
			default:
				printf("Res: %d\n", res[0]);
			}
			windowManager->inputManager.setReadPixelBuffer(false);
		}
		*/

		/*// Get the uniform locations
		modelLoc = shaderSelection.getUniformLocation("model");
		viewLoc = shaderSelection.getUniformLocation("view");
		projLoc = shaderSelection.getUniformLocation("projection");
		// Pass the matrices to the shader
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		*/
		/*Inicio algoritmo de Colisiones*/
		lighting.turnOn();

		modelLoc = lighting.getUniformLocation("model");
		viewLoc = lighting.getUniformLocation("view");
		projLoc = lighting.getUniformLocation("projection");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		modelRobot = glm::translate(modelRobot, glm::vec3(sbb1.center.x, sbb1.center.y, sbb1.center.z));
		modelRobot= glm::scale(modelRobot, glm::vec3(sbb1.ratio, sbb1.ratio, sbb1.ratio));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelRobot));
		glColor3f(0.0f,1.0f,0.0f);
		esferaColision.render();

		modelPumpkin = glm::translate(modelPumpkin, glm::vec3(sbb2.center.x, sbb2.center.y, sbb2.center.z));
		modelPumpkin = glm::scale(modelPumpkin, glm::vec3(sbb2.ratio, sbb2.ratio, sbb2.ratio));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelPumpkin));
		esferaColision.render();

		modelCroc = glm::translate(modelCroc, glm::vec3(
			(aabb1.max.x + aabb1.min.x) / 2.0f,
			(aabb1.max.y + aabb1.min.y) / 2.0f,
			(aabb1.max.z + aabb1.min.z) / 2.0f
			));
		modelCroc = glm::scale(modelCroc, glm::vec3(
			(aabb1.max.x - aabb1.min.x),
			(aabb1.max.y - aabb1.min.y),
			(aabb1.max.z - aabb1.min.z)
			));
		modelCroc = glm::scale(modelCroc, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelCroc));
		cubo.render();
		
		modelTrex = glm::translate(modelTrex, glm::vec3(
			(aabb2.max.x + aabb2.min.x) / 2.0f,
			(aabb2.max.y + aabb2.min.y) / 2.0f,
			(aabb2.max.z + aabb2.min.z) / 2.0f
			));

		modelTrex = glm::scale(modelTrex, glm::vec3(
			(aabb2.max.x - aabb2.min.x),
			(aabb2.max.y - aabb2.min.y),
			(aabb2.max.z - aabb2.min.z)
			));
		modelTrex = glm::scale(modelTrex, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelTrex));
		cubo.render();

		modelBaymax = glm::translate(modelBaymax, glm::vec3(
			(aabb3.max.x + aabb3.min.x) / 2.0f,
			(aabb3.max.y + aabb3.min.y) / 2.0f,
			(aabb3.max.z + aabb3.min.z) / 2.0f
			));
		modelBaymax = glm::scale(modelBaymax, glm::vec3(
			(aabb3.max.x - aabb3.min.x),
			(aabb3.max.y - aabb3.min.y),
			(aabb3.max.z - aabb3.min.z)
			));
		modelBaymax= glm::scale(modelBaymax, glm::vec3(0.5f, 0.5f, 0.5f));
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelBaymax));
		cubo.render();

		/*Fin algoritmo de Colisiones*/

		/*AUDIOS*/
		/*
		source0Pos_robot[0] = modelRobot[3].x;
		source0Pos_robot[1] = modelRobot[3].y;
		source0Pos_robot[2] = modelRobot[3].z;
		alSourcefv(source[0], AL_POSITION, source0Pos_robot);

		source1Pos_croc[0] = modelCroc[3].x;
		source1Pos_croc[1] = modelCroc[3].y;
		source1Pos_croc[2] = modelCroc[3].z;
		alSourcefv(source[1], AL_POSITION, source1Pos_croc);

		source2Pos_trex[0] = modelTrex[3].x;
		source2Pos_trex[1] = modelTrex[3].y;
		source2Pos_trex[2] = modelTrex[3].z;
		alSourcefv(source[2], AL_POSITION, source2Pos_trex);

		source3Pos_pumpkin[0] = modelPumpkin[3].x;
		source3Pos_pumpkin[1] = modelPumpkin[3].y;
		source3Pos_pumpkin[2] = modelPumpkin[3].z;
		alSourcefv(source[3], AL_POSITION, source3Pos_pumpkin);

		source4Pos_baymax[0] = modelBaymax[3].x;
		source4Pos_baymax[1] = modelBaymax[3].y;
		source4Pos_baymax[2] = modelBaymax[3].z;
		alSourcefv(source[4], AL_POSITION, source4Pos_baymax);

		listenerPos[0] = camera->Position.x;
		listenerPos[1] = camera->Position.y;
		listenerPos[2] = camera->Position.z;
		alListenerfv(AL_POSITION, listenerPos);

		listenerOri[0] = camera->Front.x;
		listenerOri[1] = camera->Front.y;
		listenerOri[2] = camera->Front.z;
		listenerOri[3] = camera->WorldUp.x;
		listenerOri[4] = camera->WorldUp.y;
		listenerOri[5] = camera->WorldUp.z;
		alListenerfv(AL_ORIENTATION, listenerOri);

		if (windowManager->inputManager.getKeyState()[InputCodes::u]){
			alSourcePlay(source[0]);
		}
		*/
		/*AUDIOS*/


		/*Calculo de Colisiones*/

		//colisiones de movimiento
		AABB a1, a2, a3;
		SBB s1, s2;

		//esfera y esfera
		s1.center = glm::vec3(modelRobot * glm::vec4(0, 0, 0, 1));
		s1.ratio = sbb1.ratio*0.5f;
		s2.center = glm::vec3(modelPumpkin * glm::vec4(0, 0, 0, 1));
		s2.ratio = sbb2.ratio*0.3f;
		if (testSphereSphereIntersection(s1, s2)){
			Colision::colisionPumpkin = true;
			/*alSourcePlay(source[0]);
			alSourcePlay(source[3]);*/
			std::cout << "Colision con Pumpkin:" << std::endl;
		}
		else{
			Colision::colisionPumpkin = false;
		}

		//cubo y esfera
		a1 = getAABB(
			glm::vec3(aabb1.min.x*0.5f + crocPos.x, aabb1.min.y*0.5 + crocPos.y, aabb1.min.z*0.5f + crocPos.z),
			glm::vec3(aabb1.max.x*0.5f + crocPos.x, aabb1.max.y*0.5f + crocPos.y, aabb1.max.z*0.5f + crocPos.z)
			);
		
		a2 = getAABB(
			glm::vec3(aabb2.min.x*0.05f + trexPos.x, aabb2.min.y*0.05f + trexPos.y, aabb2.min.z*0.05f + trexPos.z),
			glm::vec3(aabb2.max.x*0.05f + trexPos.x, aabb2.max.y*0.05f + trexPos.y, aabb2.max.z*0.05f + trexPos.z)
			);
		
		if (testSphereCubeIntersection(a1, s1)){
			Colision::colisionCroc = true;
			/*alSourcePlay(source[0]);
			alSourcePlay(source[1]);*/
			std::cout << "Colision con Croc:" << std::endl;
		}

		if (testSphereCubeIntersection(a2, s1)){
			Colision::colisionTrex = true;
			/*alSourcePlay(source[0]);
			alSourcePlay(source[2]);*/
			std::cout << "Colision con Trex:" << std::endl;
		}

		//cubo y cubo

		if (Colision::bajarCaja){
			baymaxPos.y -= 0.005f;
		}
		
		a3 = getAABB(
			glm::vec3(aabb3.min.x*0.1f + baymaxPos.x, aabb3.min.y*0.1f + baymaxPos.y, aabb3.min.z*0.1f + baymaxPos.z),
			glm::vec3(aabb3.max.x*0.1f + baymaxPos.x, aabb3.max.y*0.1f + baymaxPos.y, aabb3.max.z*0.1f + baymaxPos.z)
			);

		if (testCubeCubeIntersection(a1, a3)){
			/*alSourcePlay(source[1]);
			alSourcePlay(source[4]);*/
			std::cout << "Colision Baymax con Croc:" << std::endl;
			baymaxPos.y = 15.0f;
		}

		/*PICKING CON RAYO*/
		if (windowManager->inputManager.isGenerateRay()) {

			glm::vec3 o = glm::unProject(glm::vec3(windowManager->inputManager.getLastMousePos().x,
				WindowManager::screenHeight - windowManager->inputManager.getLastMousePos().y,
				0.0f), camera->GetViewMatrix(), projection, viewport);
			glm::vec3 t = glm::unProject(glm::vec3(windowManager->inputManager.getLastMousePos().x,
				WindowManager::screenHeight - windowManager->inputManager.getLastMousePos().y,
				1.0f), camera->GetViewMatrix(), projection,viewport);

			VertexColor vertex[2] = { { o, glm::vec3(0.0) }, { t, glm::vec3(0.0) } };
			glGenVertexArrays(1, &VAO);
			glGenBuffers(1, &VBO);
			glBindVertexArray(VAO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex[0]), (GLvoid*)0);
			glEnableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);

			rays.push_back(VAO);


			glm::vec3 c1 = glm::vec3(modelRobot * glm::vec4(0, 0, 0, 1));
			glm::vec3 c2 = glm::vec3(modelPumpkin * glm::vec4(0, 0, 0, 1));
			glm::vec3 dir = glm::normalize(t - o);
			float t1;

			glm::vec3 vDirToSphere = c1 - o;
			float fLineLength = glm::distance(o, t);
			t1 = glm::dot(vDirToSphere, dir);

			if (raySphereIntersect(o, t, dir, c1, sbb1.ratio, t1)){
				/*alSourcePlay(source[0]);*/
				if (angRobot == 0.0f){
					angRobot += 45.0f;
					if (angRobot > 360.0f){
						angRobot = 0.0f;
					}
				}
				else{
					angRobot= 0.0f;
				}
				std::cout << "Picking Robot" << std::endl;
			}

			vDirToSphere = c2 - o;
			fLineLength = glm::distance(o, t);
			t1 = glm::dot(vDirToSphere, dir);

			if (raySphereIntersect(o, t, dir, c2, sbb2.ratio, t1)){
				if (angPumpkin == 0.0f){
					angPumpkin += 2.0f;
					if (angPumpkin > 290.0f){
						angPumpkin = 0.0f;
					}
				}
				else{
					angPumpkin = 0.0f;
				}
				/*alSourcePlay(source[3]);*/
				std::cout << "Picking Pumpkin" << std::endl;
			}

			if (rayCubeIntersect(o, t, dir, a1)){
				if (angCroc == 0.0f){
					angCroc += 10.0f;
					if (angCroc > 290.0f){
						angCroc = 0.0f;
					}
				}
				else{
					angCroc = 0.0f;
				}
				/*alSourcePlay(source[1]);*/
				std::cout << "Picking Croc" << std::endl;
			}
			if(rayCubeIntersect(o, t, dir, a2)){
				if (angTrex == 0.0f){
					angTrex += 8.0f;
					if (angTrex > 350.0f){
						angTrex = 0.0f;
					}
				}
				else{
					angTrex = 0.0f;
				}
				/*alSourcePlay(source[2]);*/
				std::cout << "Picking Trex" << std::endl;
			}
			if (rayCubeIntersect(o, t, dir, a3)){
				if (angBaymax == 0.0f){
					angBaymax += 3.0f;
					if (angBaymax > 350.0f){
						angBaymax = 0.0f;
					}
				}
				else{
					angBaymax = 0.0f;
				}
				/*alSourcePlay(source[4]);*/
				std::cout << "Picking Baymax" << std::endl;
			}

			windowManager->inputManager.setGenerateRay(false);
		}
		/*Fin del calculo de Colisiones*/


		// Create transformations
		modelLoc = lampShader.getUniformLocation("model");
		viewLoc = lampShader.getUniformLocation("view");
		projLoc = lampShader.getUniformLocation("projection");

		// Pass the matrices to the shader
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

		// Draw the loaded model
		glm::mat4 modelL = glm::mat4();
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelL));

		for (int i = 0; i < rays.size(); i++) {
			glBindVertexArray(rays[i]);
			glDrawArrays(GL_LINES, 0, 2);
		}

		lighting.turnOn();

		windowManager->swapTheBuffers();




		glClearColor(0.2f, 0.2f, 0.2f, 0.0f);
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

