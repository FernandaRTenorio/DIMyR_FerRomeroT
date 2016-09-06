#include <iostream>

#include "Headers/InputManager.h"
#include "Headers/TimeManager.h"

float x_global, y_global;
bool click;
glm::mat4 transform;
//static bool rotar = false;

void InputManager::keyPressed(InputCodes code, float deltaTime) {
	switch (code) {
	case kEscape:
		exitApp = true;
		break;
	}
}

void InputManager::mouseMoved(float mouseX, float mouseY) {
	lastMousePos.x = mouseX;
	lastMousePos.y = mouseY;
	
	if (click == true){
		if (lastMousePos.x > x_global){
			std::cout << "Cubo rota sobre y" << lastMousePos.x << std::endl;
			//rotar = true;
			transform = glm::rotate(transform, glm::radians((x_global-lastMousePos.x)*0.05f), glm::vec3(0.0f, 1.0f, 0.0f));
		}
		if (lastMousePos.x < x_global){
			std::cout << "Cubo rota sobre -y" << lastMousePos.x << std::endl;
			transform = glm::rotate(transform, glm::radians((x_global + lastMousePos.x)*0.05f), glm::vec3(0.0f, 1.0f, 0.0f));
		}
		if (lastMousePos.y > y_global){
			transform = glm::rotate(transform, glm::radians((y_global - lastMousePos.y)*0.05f), glm::vec3(1.0f, 0.0f, 0.0f));
		}
		if (lastMousePos.y < y_global){
			transform = glm::rotate(transform, glm::radians((y_global + lastMousePos.y)*0.05f), glm::vec3(1.0f, 0.0f, 0.0f));
		}
	}
}

glm::mat4 InputManager::getTransform(){
	//transform = glm::rotate(transform, glm::radians(30.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	return transform;
}

void InputManager::mouseClicked(MouseCodes code) {
	
	switch (code) {
	case button_right:
		click = false;
		break;
	case button_left:
		click = true;
		x_global = lastMousePos.x;
		y_global = lastMousePos.y;
		std::cout << "lastMousePos.x:" << lastMousePos.x << std::endl;
		
		break;
	case button_middle:
		std::cout << "lastMousePos.x:" << lastMousePos.x << std::endl;
		std::cout << "lastMousePos.y:" << lastMousePos.y << std::endl;
		break;
	}
	//click = false;
}

void InputManager::mouseScroll(float yoffset) {
}


