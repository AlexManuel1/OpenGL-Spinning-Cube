#include "Shader.h"

Shader::Shader()
{
    shaderProgramID = 0;
    uniformModel = 0;
    uniformProjection = 0;
}

std::string Shader::ReadFile(const char *fileLocation)
{
    std::string content;
    std::ifstream shaderFile(fileLocation, std::ifstream::in);

    // check if file exists
    if (!shaderFile.is_open())
    {
        printf("Failed to read %s! File does not exist!", fileLocation);
        return "";
    }

    // copy shader code from file into memory
    std::string line;
    while (!shaderFile.eof())
    {
        std::getline(shaderFile, line);
        content.append(line + "\n");
    }

    shaderFile.close();
    return content;
}

void Shader::CreateFromFiles(const char *vertexLocation, const char *fragmentLocation)
{
    std::string vertexCode = ReadFile(vertexLocation);
    std::string fragmentCode = ReadFile(fragmentLocation);
    
    if (vertexCode == "" || fragmentCode == "")
    {
        printf("vertex shader or fragment shader file location invalid"); 
    }

    // convert strings to char arrays
    const char *vertexCodeCharArray = vertexCode.c_str();
    const char *fragmentCodeCharArray = fragmentCode.c_str();

    // compile shader code
    CompileShader(vertexCodeCharArray, fragmentCodeCharArray);
}

void Shader::CompileShader(const char *vertexCode, const char *fragmentCode)
{
    shaderProgramID = glCreateProgram();

    if (!shaderProgramID)
    {
        printf("Error creating program for shaders\n");
        return;
    }

    // add shader programs
    AddShader(shaderProgramID, vertexCode, GL_VERTEX_SHADER);
    AddShader(shaderProgramID, fragmentCode, GL_FRAGMENT_SHADER);

    // link program and make sure linking was successful
    GLint linkProgramStatus = 0;
    GLchar linkProgramLog[1024] = { 0 };
    glLinkProgram(shaderProgramID);
    glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &linkProgramStatus);
    if (!linkProgramStatus)
    {
        glGetProgramInfoLog(shaderProgramID, sizeof(linkProgramLog), NULL, linkProgramLog);
        printf("Shader program was unsuccessfully linked: %s", linkProgramLog);
        return;
    }

    // validate program
    GLint validationStatus = 0;
    GLchar validationLog[1024] = { 0 };
    glGetProgramiv(shaderProgramID, GL_VALIDATE_STATUS, &validationStatus);
    if (!validationStatus)
    {
        glGetProgramInfoLog(shaderProgramID, sizeof(validationLog), NULL, validationLog);
        printf("Shader program invalid: %s\n", validationLog);
    }

    // get uniform locations
    uniformModel = glGetUniformLocation(shaderProgramID, uniformModelName);
    uniformProjection = glGetUniformLocation(shaderProgramID, uniformProjectionName);
    uniformView = glGetUniformLocation(shaderProgramID, uniformViewName);
}

void Shader::AddShader(GLuint programID, const char* shaderCode, GLenum shaderType)
{
    // initialize shader
    GLuint shader = glCreateShader(shaderType);
    if (!shader)
    {
        printf("shader not created successfully!");
        return;
    }

    // initialize variables to pass to glShaderSource function
    const GLchar *sourceCode[1];
    sourceCode[0] = shaderCode;
    GLint sourceCodeLength[1];
    sourceCodeLength[0] = strlen(shaderCode);

    // input shader source and compile shader
    glShaderSource(shader, 1, sourceCode, sourceCodeLength);
    glCompileShader(shader);

    // catch errors for compilation
    GLint compileStatus = 0;
    GLchar compileLog[1024] = { 0 };
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);
    if (!compileStatus)
    {
        glGetShaderInfoLog(shader, sizeof(compileLog), NULL, compileLog);
        printf("Error compiling the %d shader: '%s'\n", shaderType, compileLog);
        return;
    }

    // attach shader to the program
    glAttachShader(programID, shader);
}

void Shader::UseShader()
{
    glUseProgram(shaderProgramID);
}

void Shader::ClearShader()
{
    if (shaderProgramID != 0)
    {
        glDeleteProgram(shaderProgramID);
        shaderProgramID = 0;
    }
    uniformModel = 0;
    uniformProjection = 0;
}

GLuint Shader::getModelLocation()
{
    return uniformModel;
}

GLuint Shader::getProjectionLocation()
{
    return uniformProjection;
}

GLuint Shader::getViewLocation()
{
    return uniformView;
}

Shader::~Shader()
{
    ClearShader();
}