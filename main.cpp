#include <QApplication>
#ifndef QT_OPENGL_ES
#include <GL/glut.h>
#endif
#include "mainwindow.h"

int main(int argc, char *argv[])
{
#ifndef QT_OPENGL_ES
    glutInit(&argc, argv);
#endif
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    
    return a.exec();
}
