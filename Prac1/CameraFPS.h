/*


*/
#ifndef _CameraFPS_H
#define _CameraFPS_H

//std includes
#include <string>
#include <iostream>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform2.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>

class CameraFPS
{
public:
	CameraFPS() :
		cameraPos(
		glm::vec3(0.0f, 0.0f, 3.0f)), cameraFront(
		glm::vec3(0.0f, 0.0f, -1.0f)), cameraUp(
		glm::vec3(0.0f, 1.0f, 0.0f)) {}
	~CameraFPS();


	glm::vec3 getCameraFront() {
		return cameraFront;
	}

	glm::vec3 getCameraPos() {
		return cameraPos;
	}

	glm::vec3 getCameraUp() {
		return cameraUp;
	}

protected:
	glm::vec3 cameraPos;
	glm::vec3 cameraFront;
	glm::vec3 cameraUp;

	float yaw = -90.0f;
	float pitch = 0.0f;
};

