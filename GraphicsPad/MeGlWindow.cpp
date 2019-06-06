#include <gl\glew.h>
#include "MeGlWindow.h"

MeGlWindow::MeGlWindow()
{
}

MeGlWindow::~MeGlWindow()
{
}

void MeGlWindow::initializeGL()
{
	glewInit();
}

void MeGlWindow::paintGL()
{
	glClearColor(1.0f, 0.f, 0.f, 1.f);
	glClear(GL_COLOR_BUFFER_BIT);
}
