#include <QApplication>
#include <QtWidgets>
#include <QLabel>
#include "window.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Window window;

    return a.exec();
}
