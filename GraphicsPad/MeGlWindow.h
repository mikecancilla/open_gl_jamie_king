#pragma once

#include <gl/glew.h>
#include <QtOpenGL\QGLWidget>

#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

class MeGlWindow : public QGLWidget
{
protected:
	void initializeGL() override;
	void paintGL() override;
	void sendDataToOpenGL();

	std::string readShaderCode(const char* fileName);
    void installShaders();

	bool checkStatus(GLuint objectID,
                     PFNGLGETSHADERIVPROC objectPropertyGetterFunc,
                     PFNGLGETSHADERINFOLOGPROC getInfoLogFunc,
                     GLenum statusType);
	bool checkShaderStatus(GLuint shaderID);
    bool checkProgramStatus(GLuint programID);

public:
	MeGlWindow();
	virtual ~MeGlWindow();
};

