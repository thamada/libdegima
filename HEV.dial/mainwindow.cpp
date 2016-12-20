/**
 * Copyright(c) 2013 by Tsuyoshi Hamada, Nagasaki University 
 * All rights reserved
 */ 

#include <mainwindow.h>
#include <cstdio>

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
{
  vdegima = new Vdegima();

  QWidget *cw = new QWidget();
  setCentralWidget(cw);

  QDial *dial1 = new QDial();
  dial1->setValue(50);

  QVBoxLayout *vLayout = new QVBoxLayout(cw);

  vLayout->addWidget(new QLabel(tr("By Tsuyoshi Hamada")));
  vLayout->addWidget(dial1);

  QObject::connect(dial1, SIGNAL(valueChanged(int)), this, SLOT(slot_dial1(int)));

}

MainWindow::~MainWindow()
{
    printf("~MainWindow() called. Bye-Bye\n");
    delete vdegima;
}


void MainWindow::slot_dial1(int value){
  //  static int count = 0;
  //  printf("button clicked %d: %d\n", count++, value);
  vdegima->HEV_SetStrAngle(value);
}


