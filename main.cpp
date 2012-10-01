#include <QtGui/QApplication>
#include "mainwindow.h"
#include "viewer.h"
#include "ui_mainwindow.h"

#include <QHBoxLayout>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
