/*
* collision.h
*
*  Created on: 06/09/2016
*      Author: rey
*/

#ifndef HEADERS_COLLISION_H_
#define HEADERS_COLLISION_H_

#include <float.h>
#include "Mesh.h"
#include "definition.h"

AABB getAABB(std::vector<Mesh> meshes) {
	AABB aabb;
	aabb.min.x = FLT_MAX;
	aabb.min.y = FLT_MAX;
	aabb.min.z = FLT_MAX;
	aabb.max.x = -FLT_MAX;
	aabb.max.y = -FLT_MAX;
	aabb.max.z = -FLT_MAX;

	for (int i = 0; i < meshes.size(); i++) {
		for (int j = 0; j < meshes[i].vertices.size(); j++) {
			if (meshes[i].vertices[j].Position.x < aabb.min.x)
				aabb.min.x = meshes[i].vertices[j].Position.x;
			if (meshes[i].vertices[j].Position.x > aabb.max.x)
				aabb.max.x = meshes[i].vertices[j].Position.x;
			if (meshes[i].vertices[j].Position.y < aabb.min.y)
				aabb.min.y = meshes[i].vertices[j].Position.y;
			if (meshes[i].vertices[j].Position.y > aabb.max.y)
				aabb.max.y = meshes[i].vertices[j].Position.y;
			if (meshes[i].vertices[j].Position.z < aabb.min.z)
				aabb.min.z = meshes[i].vertices[j].Position.z;
			if (meshes[i].vertices[j].Position.z > aabb.max.z)
				aabb.max.z = meshes[i].vertices[j].Position.z;
		}
	}
	aabb.center = glm::vec3((aabb.min.x + aabb.max.x) / 2.0f,
		(aabb.min.y + aabb.max.y) / 2.0f, (aabb.min.z + aabb.max.z) / 2.0f);
	aabb.dist = sqrt(
		pow(aabb.min.x - aabb.max.x, 2) + pow(aabb.min.y - aabb.max.y, 2)
		+ pow(aabb.min.z - aabb.max.z, 2));
	return aabb;
}

SBB getSBB(std::vector<Mesh> meshes) {
	AABB aabb = getAABB(meshes);
	SBB sbb;
	sbb.center = glm::vec3((aabb.min.x + aabb.max.x) / 2.0f,
		(aabb.min.y + aabb.max.y) / 2.0f, (aabb.min.z + aabb.max.z) / 2.0f);
	sbb.ratio = sqrt(
		pow(aabb.min.x - aabb.max.x, 2) + pow(aabb.min.y - aabb.max.y, 2)
		+ pow(aabb.min.z - aabb.max.z, 2)) / 2.0f;
	return sbb;
}

bool SBBvsSBB(SBB sbb1, SBB sbb2) {
	float d = glm::distance(sbb1.center, sbb2.center);
	if (d <= (sbb1.ratio + sbb2.ratio))
		return false;
	return true;
}

bool AABBvsAABB(AABB aabb1, AABB aabb2) {
	if (aabb1.min.x <= aabb2.max.x && aabb1.max.x >= aabb2.min.x &&
		aabb1.min.y <= aabb2.max.y && aabb1.max.y >= aabb2.min.y &&
		aabb1.min.z <= aabb2.max.z && aabb1.max.z >= aabb2.min.z){
		return true;
	}
	else
		return false;
}

bool AABBvsSBB(AABB aabb1, SBB sbb1) {

	bool center;
	float s, d;

	if (sbb1.center.x >= aabb1.min.x && sbb1.center.x <= aabb1.max.x &&
		sbb1.center.y >= aabb1.min.y && sbb1.center.y <= aabb1.max.y &&
		sbb1.center.z >= aabb1.min.z && sbb1.center.z <= aabb1.max.z){
		center = true;
	}
	else
		center = false;
	if (center == false){
		for (int i = 0; i < 3; i++){
			if (sbb1.center[i] < aabb1.min[i]){
				s = sbb1.center[i] - aabb1.min[i];
				d += s*s;
			}
			else if (sbb1.center[i]>aabb1.max[i]){
				s = sbb1.center[i] - aabb1.max[i];
				d += s*s;
			}
		}
	}

	if (d < (sbb1.ratio*sbb1.ratio)){
		return true;
	}
	return false;


}

#endif /* HEADERS_COLLISION_H_ */

