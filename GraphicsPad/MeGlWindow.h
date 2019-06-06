#pragma once

#include <QtOpenGL\QGLWidget>

class MeGlWindow : public QGLWidget
{
protected:
	void initializeGL() override;
	void paintGL() override;

public:
	MeGlWindow();
	virtual ~MeGlWindow();
};

