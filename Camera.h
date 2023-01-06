#pragma once

#include <iostream>
#include <stdio.h>

#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{

public:
    Camera(glm::vec3 startPosition, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed);

    void mouseControl(GLfloat xChange, GLfloat yChange);
    void keyControl(bool *keys, double deltaTime);
    glm::mat4 calcViewMatrix();

    ~Camera();

private:
    GLfloat yaw;
    GLfloat pitch;

    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 right;
    glm::vec3 up;
    glm::vec3 worldUp;

    GLfloat moveSpeed;
    GLfloat turnSpeed;

    void update();
};
