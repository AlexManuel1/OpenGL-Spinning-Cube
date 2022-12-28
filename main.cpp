#include <vector>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <cmath>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/ext.hpp>

#include "GlWindow.h"
#include "Mesh.h"
#include "Shader.h"

// initialize mesh list, shader list, and main window
std::vector<Mesh*> meshList;
std::vector<Shader*> shaderList;
GlWindow *mainWindow;

// shader code locations
static const char *vertexLocation = "Shaders/shader.vert";
static const char *fragmentLocation = "Shaders/shader.frag";

// create meshes
void CreateObjects()
{
    unsigned int indices[] = {
        0, 1,
        1, 2,
        2, 3,
        3, 0,

        0, 4,
        1, 5,
        2, 6,
        3, 7,

        4, 5,
        5, 6,
        6, 7,
        7, 4
    };

    GLfloat vertices[] = {
        -1.0f, 1.0f, -1.0f,
        1.0f, 1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
    
        -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, -1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f,
    };

    // create cube mesh
    Mesh *obj1 = new Mesh();
    obj1->CreateMesh(vertices, indices, sizeof(vertices)/sizeof(vertices[0]), sizeof(indices)/sizeof(indices[0]));
    meshList.push_back(obj1);
}

void CreateShaders()
{
    Shader *shader1 = new Shader();
    shader1->CreateFromFiles(vertexLocation, fragmentLocation);
    shaderList.push_back(shader1);
}

int Initialize()
{
    mainWindow = new GlWindow(800, 600, "Spinning Cubes");
    mainWindow->Initialize();

    glewExperimental = GL_TRUE; // allow modern extension features
    if ( glewInit() )
    {
        printf("An error occurred when initializing GLEW");
        mainWindow->destroyWindow();
        return 1;
    }

    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, mainWindow->getBufferWidth(), mainWindow->getBufferHeight());

    // initialize mesh and shaders
    CreateObjects();
    CreateShaders();

    return 0;
}

int main()
{
    // initialize glfw window, glew, create meshes and shaders
    if (Initialize())
    {
        return 1;
    }

    GLuint uniformModel = 0;
    GLuint uniformProjection = 0;

    // projection matrix
    glm::mat4 projection = glm::perspective(
        glm::radians(60.0f), 
        ((GLfloat)mainWindow->getBufferWidth())/((GLfloat)mainWindow->getBufferHeight()), 
        0.1f, 
        100.0f
    );

    meshList[0]->UpdateTranslationValuesZ(-7.0f, 0.1f, -100.0f);

    while (!mainWindow->getShouldClose())
    {
        glfwPollEvents();
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        mainWindow->handleKeyPresses(meshList[0]); // handle key presses

        shaderList[0]->UseShader();
        uniformModel = shaderList[0]->getModelLocation();
        uniformProjection = shaderList[0]->getProjectionLocation();

        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(meshList[0]->GetModelMatrix()));
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));

        meshList[0]->RenderMesh();
        glUseProgram(0);
        mainWindow->swapBuffers();
    }

    return 0;
}