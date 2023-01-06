#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Mesh.h"

class GlWindow 
{

public:
    GlWindow();

    GlWindow(GLint windowWidth, GLint windowHeight, std::string windowTitle);
    int Initialize();

    int getBufferWidth() { return bufferWidth; }
    int getBufferHeight() { return bufferHeight; }

    bool getShouldClose() { return glfwWindowShouldClose(window); }
    void swapBuffers() { return glfwSwapBuffers(window); }

    static void handleKeyPresses(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void handleMouseMovement(GLFWwindow* window, double xpos, double ypos);
    
    bool* getKeys() { return keys; }
    GLfloat getXChange();
    GLfloat getYChange();

    void destroyWindow();
    
    ~GlWindow();

private:
    GLFWwindow *window;
    int bufferWidth, bufferHeight;
    GLint width, height;
    std::string title;
    bool keys[1024];

    GLfloat lastX;
    GLfloat lastY;
    GLfloat xChange;
    GLfloat yChange;
    bool isFirstMouseMove;
};
