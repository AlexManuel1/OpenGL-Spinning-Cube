#include "GlWindow.h"

GlWindow::GlWindow()
{
    width = 800;
    height = 600;
    title = "window";

    for (int i = 0; i < 1024; i++)
    {
        keys[i] = false;
    }

    isFirstMouseMove = true;
}

GlWindow::GlWindow(GLint windowWidth, GLint windowHeight, std::string windowTitle)
{
    width = windowWidth;
    height = windowHeight;
    title = windowTitle;

    for (int i = 0; i < 1024; i++)
    {
        keys[i] = false;
    }

    isFirstMouseMove = true;
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

    // set callbacks for key press and movement
    glfwSetKeyCallback(window, handleKeyPresses);
    glfwSetCursorPosCallback(window, handleMouseMovement);

    // lock cursor to window and hide it
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // associate this class with GLFWwindow object
    glfwSetWindowUserPointer(window, this);

    return 0;
}

void GlWindow::handleKeyPresses(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    GlWindow *w = static_cast<GlWindow*>(glfwGetWindowUserPointer(window));

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
        {
            w->keys[key] = true;
        }
        else if (action == GLFW_RELEASE)
        {
            w->keys[key] = false;
        }
    }
}

void GlWindow::handleMouseMovement(GLFWwindow *window, double xpos, double ypos)
{
    GlWindow *w = static_cast<GlWindow*>(glfwGetWindowUserPointer(window));

    if (w->isFirstMouseMove)
    {
        w->lastX = xpos;
        w->lastY = ypos;
        w->isFirstMouseMove = false;
    }

    w->xChange = xpos - w->lastX;
    w->yChange = w->lastY - ypos;

    w->lastX = xpos;
    w->lastY = ypos;
}

GLfloat GlWindow::getXChange()
{
    GLfloat change = xChange;
    xChange = 0.0f;
    return change;
}

GLfloat GlWindow::getYChange()
{
    GLfloat change = yChange;
    yChange = 0.0f;
    return change;
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
    destroyWindow();
}
