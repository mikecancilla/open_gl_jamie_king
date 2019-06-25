#include <Qt\qapplication.h>
#include <Qt\qwidget.h>
#include <MeWidget.h>

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

    MeWidget widg;
    widg.show();

	//MeGlWindow meWindow;
	//meWindow.show();

	return app.exec();
}