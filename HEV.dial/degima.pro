#-------------------------------------------------
#
# Project created by QtCreator 2013-01-12T15:59:56
#
#-------------------------------------------------

QT       += core gui

TARGET = degima
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        HevCnt.cpp \
        Vdegima.cpp \


HEADERS  += mainwindow.h HevCnt.h

unix:!macx:!symbian: LIBS += -L/usr/local/lib/zmp/ -lhevcontrol

INCLUDEPATH += /usr/local/include/zmp
DEPENDPATH += /usr/local/include/zmp

unix:!macx:!symbian: LIBS += -L/usr/local/lib/zmp/ -lcanif

INCLUDEPATH += /usr/local/include/zmp
DEPENDPATH += /usr/local/include/zmp

unix:!macx:!symbian: LIBS += -L/home/robocar_HV/work/degima -ldegima

INCLUDEPATH += /home/robocar_HV/work/degima
DEPENDPATH += /home/robocar_HV/work/degima


