#include "Camera.h"

Camera::Camera(glm::vec3 startPosition, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed)
{
    yaw = startYaw;
    pitch = startPitch;
    
    position = startPosition;
    front = glm::vec3(0.0f, 0.0f, -1.0f);
    worldUp = glm::vec3(0.0f, 1.0f, 0.0f);

    moveSpeed = startMoveSpeed;
    turnSpeed = startTurnSpeed;

    update();
}

void Camera::update()
{
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(front);

    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}

void Camera::keyControl(bool *keys, double deltaTime)
{
    GLfloat velocity = deltaTime * moveSpeed;

    if (keys[GLFW_KEY_W])
    {
        position += (velocity * front);
    }
    if (keys[GLFW_KEY_S])
    {
        position -= (velocity * front);
    }
    if (keys[GLFW_KEY_D])
    {
        position += (velocity * right);
    }
    if (keys[GLFW_KEY_A])
    {
        position -= (velocity * right);
    }

}

void Camera::mouseControl(GLfloat xChange, GLfloat yChange)
{
    yaw += (xChange * turnSpeed);
    pitch += (yChange * turnSpeed);

    if (pitch >= 89.0f)
    {
        pitch = 89.0f;
    }
    else if (pitch <= -89.0f)
    {
        pitch = -89.0f;
    }

    update();
}

glm::mat4 Camera::calcViewMatrix()
{
    return glm::lookAt(position, position + front, worldUp);
}

Camera::~Camera() {}

