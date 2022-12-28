#include "Mesh.h"

Mesh::Mesh()
{
    VAO = 0;
    VBO = 0;
    IBO = 0;
    indexCount = 0;
    model = glm::mat4(1.0f);
}

void Mesh::CreateMesh(GLfloat *vertices, unsigned int *indices, unsigned int numOfVertices, unsigned int numOfIndices)
{
    indexCount = numOfIndices;

    // generate and bind VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // generate and bind VBOs
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * numOfVertices, vertices, GL_STATIC_DRAW);

    // generate and bind IBOs
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * numOfIndices, indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

void Mesh::RenderMesh()
{
    UpdateModel(); // update x,y,z values for translation and rotation
    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glDrawElements(GL_LINES, indexCount, GL_UNSIGNED_INT, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Mesh::UpdateModel()
{
    model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(translation[0].value, translation[1].value, translation[2].value));
    model = glm::rotate(model, rotation[0].value * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, rotation[1].value * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, rotation[2].value * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));

}  

void Mesh::HandleTranslation(int coord, bool changeDirection)
{
    if (coord > 2 || coord < 0)
    {
        std::cout << "invalid coordinate: must be 0, 1, or 2" << std::endl;
        return;
    }

    GLfloat initialDirection = translation[coord].direction;
    // change direction if needed
    if (changeDirection)
    {
        translation[coord].direction = !translation[coord].direction;
    }
    // handle translation
    if (translation[coord].direction)
    {
        translation[coord].value += translation[coord].delta;
    }
    else 
    {
        translation[coord].value -= translation[coord].delta;
    }
    // update
    UpdateModel();
    // restore original delta
    translation[coord].direction = initialDirection;
}

void Mesh::HandleRotation(int coord, bool changeDirection)
{
    if (coord > 2 || coord < 0)
    {
        std::cout << "invalid coordinate: must be 0, 1, or 2" << std::endl;
        return;
    }

    GLfloat initialDelta = rotation[coord].delta;
    // change direction if needed
    if (changeDirection)
    {
        rotation[coord].delta = -rotation[coord].delta;
    }
    // handle rotation
    if (rotation[coord].value >= rotation[coord].maxValue)
    {
        rotation[coord].value = 0;
    }
    rotation[coord].value += rotation[coord].delta;
    // update
    UpdateModel();
    // restore original delta
    rotation[coord].delta = initialDelta;
}

void Mesh::ClearMesh()
{
    if (IBO != 0)
    {
        glDeleteBuffers(1, &IBO);
        IBO = 0;
    }
    if (VBO != 0)
    {
        glDeleteBuffers(1, &VBO);
        VBO = 0;
    }
    if (VAO != 0)
    {
        glDeleteVertexArrays(1, &VAO);
        VAO = 0;
    }

    indexCount = 0;
}

Mesh::~Mesh()
{
    ClearMesh();
}
