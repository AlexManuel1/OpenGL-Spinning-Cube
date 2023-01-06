#pragma once

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>

#include <GL/glew.h>

class Shader
{

public:
    Shader();

    std::string ReadFile(const char *fileLocation);
    void CreateFromFiles(const char *vertexLocation, const char *fragmentLocation);

    void UseShader();
    void ClearShader();

    GLuint getModelLocation();
    GLuint getProjectionLocation();
    GLuint getViewLocation();

    ~Shader();

private:
    GLuint shaderProgramID, uniformModel, uniformProjection, uniformView;
    const GLchar *uniformModelName = "model";
    const GLchar *uniformProjectionName = "projection";
    const GLchar *uniformViewName = "view";

    void CompileShader(const char *vertexCode, const char *fragmentCode);
    void AddShader(GLuint programID, const char* shaderCode, GLenum shaderType);
};
