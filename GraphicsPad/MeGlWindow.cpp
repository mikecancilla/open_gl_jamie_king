#include <gl\glew.h>
#include <iostream>
#include <string>
#include <fstream>
#include <QtGui/QMouseEvent>
#include <QtGui/QKeyEvent>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtx/transform.hpp>
#include <Primitives/Vertex.h>
#include <Primitives/ShapeGenerator.h>
#include "MeGlWindow.h"
#include "Camera.h"

const float X_DELTA = 0.1f;
const uint NUM_VERTICIES_PER_TRI = 3;
const uint NUM_FLOATS_PER_VERTICE = 6;
const uint VERTEX_BYTE_SIZE = NUM_FLOATS_PER_VERTICE * sizeof(float);
const uint TRIANGLE_BYTE_SIZE = NUM_VERTICIES_PER_TRI * VERTEX_BYTE_SIZE;
const uint MAX_TRIS = 20;

GLuint programID;
Camera camera;
GLint fullTransformUniformLocation;

GLuint theBufferID;

GLuint cubeNumIndices;
GLuint arrowNumIndices;

GLuint cubeVertexArrayObjectID;
GLuint arrowVertexArrayObjectID;

GLuint cubeIndexDataByteOffset;
GLuint arrowIndexDataByteOffset;

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

void MeGlWindow::sendDataToOpenGL()
{
    //ShapeData shape = ShapeGenerator::makeTriangle();
    ShapeData cube = ShapeGenerator::makeCube();
    ShapeData arrow = ShapeGenerator::makeArrow();

    GLCall(glGenBuffers(1, &theBufferID));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, theBufferID));
    GLCall(glBufferData(GL_ARRAY_BUFFER,
        cube.vertexBufferSize() + cube.indexBufferSize() +
        arrow.vertexBufferSize() + arrow.indexBufferSize(),
        0, GL_STATIC_DRAW));

    GLsizeiptr currentOffset = 0;
    GLCall(glBufferSubData(GL_ARRAY_BUFFER, currentOffset, cube.vertexBufferSize(), cube.vertices));
    currentOffset += cube.vertexBufferSize();
    GLCall(glBufferSubData(GL_ARRAY_BUFFER, currentOffset, cube.indexBufferSize(), cube.indices));
    currentOffset += cube.indexBufferSize();
    GLCall(glBufferSubData(GL_ARRAY_BUFFER, currentOffset, arrow.vertexBufferSize(), arrow.vertices));
    currentOffset += arrow.vertexBufferSize();
    GLCall(glBufferSubData(GL_ARRAY_BUFFER, currentOffset, arrow.indexBufferSize(), arrow.indices));

    cubeNumIndices = cube.numIndices;
    arrowNumIndices = arrow.numIndices;

    GLCall(glGenVertexArrays(1, &cubeVertexArrayObjectID));
    GLCall(glGenVertexArrays(1, &arrowVertexArrayObjectID));

    // Setup a cube vertex array object
    GLCall(glBindVertexArray(cubeVertexArrayObjectID));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, theBufferID));
    GLCall(glEnableVertexAttribArray(0));
    GLCall(glEnableVertexAttribArray(1));
    GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, 0));
    GLCall(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)(sizeof(float) * 3)));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, theBufferID));

    // Setup an arrow vertex array object
    GLCall(glBindVertexArray(arrowVertexArrayObjectID));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, theBufferID));
    GLCall(glEnableVertexAttribArray(0));
    GLCall(glEnableVertexAttribArray(1));
    GLuint arrowByteOffset = cube.vertexBufferSize() + cube.indexBufferSize();
    GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)(arrowByteOffset)));
    GLCall(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)(arrowByteOffset + sizeof(float) * 3)));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, theBufferID));

    cubeIndexDataByteOffset = cube.vertexBufferSize();
    arrowIndexDataByteOffset = arrowByteOffset + arrow.vertexBufferSize();

    cube.cleanup();
    arrow.cleanup();
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

    // Slower way using Uniforms instead of instance data

	glm::mat4 fullTransformMatrix;
    glm::mat4 viewToProjectionMatrix = glm::perspective(45.2f, ((float)width()) / height(), 0.1f, 10.f);
    glm::mat4 worldToViewMatrix = camera.getWorldToViewMatrix();
    glm::mat4 worldToProjectionMatrix = viewToProjectionMatrix * worldToViewMatrix;

    // Cube
    GLCall(glBindVertexArray(cubeVertexArrayObjectID));
    glm::mat4 model1ToWorldMatrix = 
        glm::translate(glm::vec3(-2.f, 0.f, -3.f)) *
        glm::rotate(36.f, glm::vec3(1.f, 0.f, 0.f));
    fullTransformMatrix = worldToProjectionMatrix * model1ToWorldMatrix;
    // Less optimal using uniforms because we have to send the data down each time
    // And DrawElements is called twice
    GLCall(glUniformMatrix4fv(fullTransformUniformLocation, 1, GL_FALSE, &fullTransformMatrix[0][0]));
    GLCall(glDrawElements(GL_TRIANGLES, cubeNumIndices, GL_UNSIGNED_SHORT, (void*)cubeIndexDataByteOffset));

    glm::mat4 model2ToWorldMatrix = 
        glm::translate(glm::vec3(2.f, 0.f, -3.75f)) *
        glm::rotate(126.f, glm::vec3(0.f, 1.f, 0.f));
    fullTransformMatrix = worldToProjectionMatrix * model2ToWorldMatrix;
    // Less optimal using uniforms because we have to send the data down each time
    // And DrawElements is called twice
    glUniformMatrix4fv(fullTransformUniformLocation, 1, GL_FALSE, &fullTransformMatrix[0][0]);
    GLCall(glDrawElements(GL_TRIANGLES, cubeNumIndices, GL_UNSIGNED_SHORT, (void*)cubeIndexDataByteOffset));

    // Arrow
    GLCall(glBindVertexArray(arrowVertexArrayObjectID));
    glm::mat4 arrowModelToWorldMatrix = glm::translate(glm::vec3(0.f, 0.f, -3.f));
    fullTransformMatrix = worldToProjectionMatrix * arrowModelToWorldMatrix;
    // Less optimal using uniforms because we have to send the data down each time
    // And DrawElements is called twice
    glUniformMatrix4fv(fullTransformUniformLocation, 1, GL_FALSE, &fullTransformMatrix[0][0]);
    GLCall(glDrawElements(GL_TRIANGLES, arrowNumIndices, GL_UNSIGNED_SHORT, (void*)arrowIndexDataByteOffset));
}

void MeGlWindow::mouseMoveEvent(QMouseEvent *e)
{
	camera.mouseUpdate(glm::vec2(e->x(), e->y()));
	repaint();
}

void MeGlWindow::keyPressEvent(QKeyEvent * e)
{
	switch(e->key())
	{
	    case Qt::Key::Key_W:
		    camera.moveForward();
		break;
	    case Qt::Key::Key_S:
		    camera.moveBackward();
		break;
	    case Qt::Key::Key_A:
		    camera.strafeLeft();
		break;
	    case Qt::Key::Key_D:
		    camera.strafeRight();
		break;
	    case Qt::Key::Key_R:
		    camera.moveUp();
		break;
	    case Qt::Key::Key_F:
		    camera.moveDown();
		break;
	}

	repaint();
}

bool MeGlWindow::checkStatus(GLuint objectID,
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

bool MeGlWindow::checkShaderStatus(GLuint shaderID)
{
    return checkStatus(shaderID, glGetShaderiv, glGetShaderInfoLog, GL_COMPILE_STATUS);
}

bool MeGlWindow::checkProgramStatus(GLuint programID)
{
    return checkStatus(programID, glGetProgramiv, glGetProgramInfoLog, GL_LINK_STATUS);
}

std::string MeGlWindow::readShaderCode(const char* fileName)
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

void MeGlWindow::installShaders()
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

	// The preferred way to set shader variable locations is in shader code,
	//  but if your version of OpenGL does not support setting shader variable locations,
	//  then use the following 2 ways:

	// Way 1: Optional way to SET the location of a shader variable.  Must do before linking
	//glBindAttribLocation(programID, 2, "position");

	glLinkProgram(programID);
   
	if( !checkProgramStatus(programID) )
        return;

	// Way 2: Optional way to get the layout location of a variable in the shader, let the linker decide
	//GLint positionLocation = glGetAttribLocation(programID, "position");
	//GLint colorLocation = glGetAttribLocation(programID, "vertexColor");
	//GLint transformLocation = glGetAttribLocation(programID, "fullTransformMatrix");

	glDeleteShader(vertexShaderID);
    glDeleteShader(fragmentShaderID);

    GLCall(glUseProgram(programID));
}

// Vertex array objects store the state of the vertex attrib pointers
/*
void MeGlWindow::setupVertexArrays()
{
    GLCall(glGenVertexArrays(1, &cubeVertexArrayObjectID));
    GLCall(glGenVertexArrays(1, &arrowVertexArrayObjectID));

    // Setup a cube vertex array object
    GLCall(glBindVertexArray(cubeVertexArrayObjectID));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, cubeVertexBufferID));
    GLCall(glEnableVertexAttribArray(0));
    GLCall(glEnableVertexAttribArray(1));
    GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, 0));
    GLCall(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)(sizeof(float) * 3)));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cubeIndexBufferID));

    // Setup an arrow vertex array object
    GLCall(glBindVertexArray(arrowVertexArrayObjectID));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, arrowVertexBufferID));
    GLCall(glEnableVertexAttribArray(0));
    GLCall(glEnableVertexAttribArray(1));
    GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, 0));
    GLCall(glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)(sizeof(float) * 3)));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, arrowIndexBufferID));
}
*/

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
	setMouseTracking(true);

	glewInit();
    glEnable(GL_DEPTH_TEST);

    sendDataToOpenGL();
    //setupVertexArrays();
    installShaders();

    fullTransformUniformLocation = glGetUniformLocation(programID, "fullTransformMatrix");
}
