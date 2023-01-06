#pragma once

#include <stdio.h>
#include <iostream>
#include <GL/glew.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

class Mesh
{
public:
    Mesh();
    void CreateMesh(GLfloat *vertices, unsigned int *indices, unsigned int numOfVertices, unsigned int numOfIndices);
    void RenderMesh();
    void ClearMesh();

    ~Mesh();

private:
    GLuint VAO, VBO, IBO;
    GLsizei indexCount;
};
