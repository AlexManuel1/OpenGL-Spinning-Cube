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

    void UpdateTranslationValuesX(GLfloat value, GLfloat delta, GLfloat max) {Coordinate c = {value, delta, max, true}; translation[0] = c;} ;
    void UpdateTranslationValuesY(GLfloat value, GLfloat delta, GLfloat max) {Coordinate c = {value, delta, max, true}; translation[1] = c;} ;
    void UpdateTranslationValuesZ(GLfloat value, GLfloat delta, GLfloat max) {Coordinate c = {value, delta, max, true}; translation[2] = c;} ;
    void UpdateRotationValuesX(GLfloat value, GLfloat delta, GLfloat max) {Coordinate c = {value, delta, max, true}; rotation[0] = c;} ;
    void UpdateRotationValuesY(GLfloat value, GLfloat delta, GLfloat max) {Coordinate c = {value, delta, max, true}; rotation[1] = c;} ;
    void UpdateRotationValuesZ(GLfloat value, GLfloat delta, GLfloat max) {Coordinate c = {value, delta, max, true}; rotation[2] = c;} ;

    void UpdateModel();
    void HandleRotation(int coord, bool changeDirection);
    void HandleTranslation(int coord, bool changeDirection);

    glm::mat4 GetModelMatrix() { return model; };

    ~Mesh();

private:
    GLuint VAO, VBO, IBO;
    GLsizei indexCount;
    glm::mat4 model;
    const GLfloat toRadians = 3.14159265f / 180.0f;

    struct Coordinate {
        GLfloat value;
        GLfloat delta;
        GLfloat maxValue;
        GLboolean direction;
    };

    Coordinate translation[3] = {
        {0.0f, 0.1f, 5.0f, true},
        {0.0f, 0.1f, 5.0f, true},
        {0.0f, 0.1f, 5.0f, true} 
    };

    Coordinate rotation[3] = {
        {0.0f, 1.0f, 360.0f, true},
        {0.0f, 1.0f, 360.0f, true},
        {0.0f, 1.0f, 360.0f, true}
    };

};
