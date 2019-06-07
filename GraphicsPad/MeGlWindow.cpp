#include <gl\glew.h>
#include "MeGlWindow.h"

extern const char* vertexShaderCode;
extern const char* fragmentShaderCode;

void sendDataToOpenGL()
{
    GLfloat verts[] =
    {
         0.f,  0.f, // 0
         1.f,  0.f,  0.f,
         1.f,  1.f, // 1
         1.f,  0.f,  0.f,
        -1.f,  1.f, // 2
         1.f,  0.f,  0.f,
        -1.f, -1.f, // 3
         1.f,  0.f,  0.f,
         1.f, -1.f,  // 4
         1.f,  0.f,  0.f,
    };

    GLuint vertexBufferID;
    glGenBuffers(1, &vertexBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)(sizeof(float) * 2));

    // 0, 1, 2 -> 1st triangle
    // 0, 3, 4 -> 2nd triangle
    GLushort indicies[] = { 0,1,2, 0,3,4 };
    GLuint indexBufferID;
    glGenBuffers(1, &indexBufferID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);
}

void installShaders()
{
    GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    const char* adapter[1];
    adapter[0] = vertexShaderCode;
    glShaderSource(vertexShaderID, 1, adapter, 0);
    adapter[0] = fragmentShaderCode;
    glShaderSource(fragmentShaderID, 1, adapter, 0);

    glCompileShader(vertexShaderID);
    glCompileShader(fragmentShaderID);

    GLuint programID = glCreateProgram();
    glAttachShader(programID, vertexShaderID);
    glAttachShader(programID, fragmentShaderID);
    glLinkProgram(programID);

    glUseProgram(programID);
}

MeGlWindow::MeGlWindow()
{
}

MeGlWindow::~MeGlWindow()
{
}

void MeGlWindow::initializeGL()
{
	glewInit();
    sendDataToOpenGL();
    installShaders();
}

void MeGlWindow::paintGL()
{
	glClearColor(0.1f, 0.1f, 0.8f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);

    glViewport(0, 0, width(), height());
    //glDrawArrays(GL_TRIANGLES, 0, 6);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
}
