#include "GlWindow.h"

GlWindow::GlWindow()
{
    width = 800;
    height = 600;
    title = "window";
}

GlWindow::GlWindow(GLint windowWidth, GLint windowHeight, std::string windowTitle)
{
    width = windowWidth;
    height = windowHeight;
    title = windowTitle;
}

int GlWindow::Initialize()
{
    // initialize glfw
    if (!glfwInit()) 
    {
        printf("An error occurred when initializing GLFW");
        glfwTerminate();
        return 1;
    }

    // set window hints
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // create window
    window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (!window)
    {
        printf("An error occurred when creating GLFW window");
        glfwTerminate();
        return 1;
    }

    glfwGetFramebufferSize(window, &bufferWidth, &bufferHeight);
    glfwMakeContextCurrent(window);

    return 0;
}

void GlWindow::handleKeyPresses(Mesh *mesh)
{
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        mesh->HandleRotation(1, false);
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        mesh->HandleRotation(1, true);
    }
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        mesh->HandleRotation(0, true);
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        mesh->HandleRotation(0, false);
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        mesh->HandleTranslation(2, true);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        mesh->HandleTranslation(2, false);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        mesh->HandleTranslation(0, true);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        mesh->HandleTranslation(0, false);
    }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    {
        mesh->HandleTranslation(1, false);
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    {
        mesh->HandleTranslation(1, true);
    }
}

void GlWindow::destroyWindow()
{
    glfwDestroyWindow(window);
    glfwTerminate();
    width, height = 0;
    bufferWidth, bufferHeight = 0;
}

GlWindow::~GlWindow()
{
    glfwDestroyWindow(window);
    glfwTerminate();
}
