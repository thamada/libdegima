/**
 * Copyright(c) 2013 by Tsuyoshi Hamada, Nagasaki University 
 * All rights reserved
 */ 

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include <QtGui/QMainWindow>

#include "DriveLog.h"
using namespace degima;
#include "Vdegima.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
  MainWindow(QWidget *parent = 0);
  ~MainWindow();
  Vdegima *vdegima;

public slots:
  void slot_dial1(int);

};


#endif // MAINWINDOW_H
