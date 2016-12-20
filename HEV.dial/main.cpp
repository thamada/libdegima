/**
 * Copyright(c) 2013 by Tsuyoshi Hamada, Nagasaki University 
 * All rights reserved
 */

#include <QtGui>
#include <QtGui/QApplication>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setApplicationName("MyQtApp");
    app.setOrganizationName("MyOrganization");

    MainWindow w;
    w.show();

    return app.exec();
}
