/*
 * definition.h
 *
 *  Created on: 06/09/2016
 *      Author: rey
 */

#ifndef HEADERS_DEFINITION_H_
#define HEADERS_DEFINITION_H_

#include <glm/glm.hpp>
#include <GL/glew.h>

typedef struct _VertexColor {

	_VertexColor() {
	}

	_VertexColor(glm::vec3 position, glm::vec3 color,glm::vec2 texture) {
		this->position = position;
		this->color = color;
		this->texture = texture;
	}

	glm::vec3 position;
	glm::vec3 color;
	glm::vec2 texture;
} VertexColor;

#endif /* HEADERS_DEFINITION_H_ */
