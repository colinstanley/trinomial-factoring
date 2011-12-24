#include <QApplication>
#include "MathApp.h"

int main(int argc, char* argv[]) {
	QApplication app(argc, argv);
    MathApp *dialog = new MathApp;
	dialog->show();
	return app.exec();
}
