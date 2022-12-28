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

    void handleKeyPresses(Mesh *mesh);

    void destroyWindow();
    
    ~GlWindow();

private:
    GLFWwindow *window;
    int bufferWidth, bufferHeight;
    GLint width, height;
    std::string title;
};
