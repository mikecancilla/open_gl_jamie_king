#include <gl\glew.h>
#include <iostream>
#include <string>
#include <fstream>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <Primitives/Vertex.h>
#include <Primitives/ShapeGenerator.h>
#include "MeGlWindow.h"

const float X_DELTA = 0.1f;
const uint NUM_VERTICIES_PER_TRI = 3;
const uint NUM_FLOATS_PER_VERTICE = 6;
const uint VERTEX_BYTE_SIZE = NUM_FLOATS_PER_VERTICE * sizeof(float);
const uint TRIANGLE_BYTE_SIZE = NUM_VERTICIES_PER_TRI * VERTEX_BYTE_SIZE;
const uint MAX_TRIS = 20;
GLuint programID;
GLuint numIndices;

uint numTris = 1;

void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        std::cout << "[OpenGL Error] (" << error << "): " << function <<
            " " << file << ":" << line << std::endl;
        return false;
    }

    return true;
}

void sendDataToOpenGL()
{
    //ShapeData shape = ShapeGenerator::makeTriangle();
    ShapeData shape = ShapeGenerator::makeCube();

    GLuint vertexBufferID;
    GLCall(glGenBuffers(1, &vertexBufferID));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID));
//    GLCall(glBufferData(GL_ARRAY_BUFFER, MAX_TRIS * TRIANGLE_BYTE_SIZE, NULL, GL_STATIC_DRAW));
    GLCall(glBufferData(GL_ARRAY_BUFFER, shape.vertexBufferSize(), shape.vertices, GL_STATIC_DRAW));
    GLCall(glEnableVertexAttribArray(0));
    GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, 0));
    GLCall(glEnableVertexAttribArray(1));
    GLCall(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)(sizeof(float) * 3)));

    GLuint indexBufferID;
    glGenBuffers(1, &indexBufferID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, shape.indexBufferSize(), shape.indices, GL_STATIC_DRAW);

    numIndices = shape.numIndices;

    shape.cleanup();
}

void sendAnotherTriToOpenGL()
{
    if(numTris == MAX_TRIS)
        return;

    const GLfloat THIS_TRI_X = -1 + numTris * X_DELTA;

    GLfloat thisTri[] =
    {
        THIS_TRI_X, 1.0f, 0.0f,
        1.0f, 0.0f, 0.0f,

        THIS_TRI_X + X_DELTA, 1.0f, 0.0f,
        1.0f, 0.0f, 0.0f,

        THIS_TRI_X, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
    };

    GLCall(glBufferSubData(GL_ARRAY_BUFFER,
                           numTris * TRIANGLE_BYTE_SIZE,
                           TRIANGLE_BYTE_SIZE,
                           thisTri));
    numTris++;
}

void MeGlWindow::paintGL()
{
    GLCall(glClearColor(0.f, 0.f, 0.f, 1.f));
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
    GLCall(glViewport(0, 0, width(), height()));

    glm::mat4 projectionMatrix = glm::perspective(45.f, ((float)width()) / height(), 0.1f, 10.f);
    glm::mat4 projectionTranslationMatrix = glm::translate(projectionMatrix, glm::vec3(0, 0, -3.0f));
    glm::mat4 fullTransformMatrix = glm::rotate(projectionTranslationMatrix, 54.f, glm::vec3(1.f, 0.f, 0.f));

    GLint fullTransformMatrixUniformLocation = glGetUniformLocation(programID, "fullTransformMatrix");
//    GLint modelTransformMatrixUniformLocation = glGetUniformLocation(programID, "modelTransformMatrix");
//    GLint projectionMatrixUniformLocation = glGetUniformLocation(programID, "projectionMatrix");

    GLCall(glUniformMatrix4fv(fullTransformMatrixUniformLocation, 1, GL_FALSE, &fullTransformMatrix[0][0]));
//    GLCall(glUniformMatrix4fv(modelTransformMatrixUniformLocation, 1, GL_FALSE, &modelTransformMatrix[0][0]));
//    GLCall(glUniformMatrix4fv(projectionMatrixUniformLocation, 1, GL_FALSE, &projectionMatrix[0][0]));

    GLCall(glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_SHORT, 0));

/*
    GLint dominatingColorUniformLocation = glGetUniformLocation(programID, "dominatingColor");
    GLint yFlipUniformLocation = glGetUniformLocation(programID, "yFlip");

    glm::vec3 dominatingColor(0, 1, 0);
    glUniform3fv(dominatingColorUniformLocation, 1, &dominatingColor[0]);
    glUniform1f(yFlipUniformLocation, 1.0f);
    GLCall(glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, 0));

    dominatingColor.r = 0;
    dominatingColor.b = 1;
    glUniform3fv(dominatingColorUniformLocation, 1, &dominatingColor[0]);
    glUniform1f(yFlipUniformLocation, -1.0f);
    GLCall(glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, 0));
*/
    //sendAnotherTriToOpenGL();
    //GLCall(glDrawArrays(GL_TRIANGLES, (numTris - 1) * NUM_VERTICIES_PER_TRI, NUM_VERTICIES_PER_TRI));
}

bool checkStatus(GLuint objectID,
                 PFNGLGETSHADERIVPROC objectPropertyGetterFunc,
                 PFNGLGETSHADERINFOLOGPROC getInfoLogFunc,
                 GLenum statusType)
{
    GLint status;
    objectPropertyGetterFunc(objectID, statusType, &status);
    if (status != GL_TRUE)
    {
        GLint infoLogLength;
        objectPropertyGetterFunc(objectID, GL_INFO_LOG_LENGTH, &infoLogLength);
        GLchar* buffer = new GLchar[infoLogLength];

        GLsizei bufferSize;
        getInfoLogFunc(objectID, infoLogLength, &bufferSize, buffer);
        std::cout << buffer << std::endl;

        delete[] buffer;
        return false;
    }

    return true;
}

bool checkShaderStatus(GLuint shaderID)
{
    return checkStatus(shaderID, glGetShaderiv, glGetShaderInfoLog, GL_COMPILE_STATUS);
}

bool checkProgramStatus(GLuint programID)
{
    return checkStatus(programID, glGetProgramiv, glGetProgramInfoLog, GL_LINK_STATUS);
}

std::string readShaderCode(const char* fileName)
{
    std::ifstream meInput(fileName);

    if (!meInput.good())
    {
        std::cout << "File failed to load..." << fileName;
        exit(1);
    }

    return std::string(
        std::istreambuf_iterator<char>(meInput),
        std::istreambuf_iterator<char>()
    );
}

void installShaders()
{
    GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    const char* adapter[1];
    std::string temp = readShaderCode("VertexShaderCode.glsl");
    adapter[0] = temp.c_str();
    glShaderSource(vertexShaderID, 1, adapter, 0);
    temp = readShaderCode("FragmentShaderCode.glsl");
    adapter[0] = temp.c_str();
    glShaderSource(fragmentShaderID, 1, adapter, 0);

    glCompileShader(vertexShaderID);
    glCompileShader(fragmentShaderID);

    if (!checkShaderStatus(vertexShaderID) ||
        !checkShaderStatus(fragmentShaderID))
        return;

    programID = glCreateProgram();
    glAttachShader(programID, vertexShaderID);
    glAttachShader(programID, fragmentShaderID);
    glLinkProgram(programID);

   
	if( !checkProgramStatus(programID) )
        return;

	glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);

    GLCall(glUseProgram(programID));
}

MeGlWindow::MeGlWindow()
{
}

MeGlWindow::~MeGlWindow()
{
	glUseProgram(0);
	glDeleteProgram(programID);
}

void MeGlWindow::initializeGL()
{
	glewInit();
    glEnable(GL_DEPTH_TEST);
    sendDataToOpenGL();
    installShaders();
}
