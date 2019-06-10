#pragma once

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

public:
	MeGlWindow();
	virtual ~MeGlWindow();
};

