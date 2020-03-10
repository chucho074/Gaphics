#pragma once
#include <iostream>
#include <vector>
#include "CVertexBuffer.h"

#include "glm/vec3.hpp" // glm::vec3
#include "glm/vec4.hpp" // glm::vec4
#include "glm/mat4x4.hpp" // glm::mat4
#include "glm/gtc/matrix_transform.hpp" // glm::translate, glm::rotate, glm::scale, glm::perspective


struct SimpleVertex {
	glm::vec3 Pos;
	glm::vec2 Tex;
};

class Mesh {
public:
	Mesh(void * Device, void * DContext, std::vector<SimpleVertex> & vertices, std::vector<DWORD> & indices );
	Mesh(const Mesh & inMesh);
	void Draw();
private:
	void * DContx;



};

