#-------------------------------------------------
#
# Project created by QtCreator 2016-08-12T21:13:54
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = EditorTexto
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    document.cpp \
    namefiledialog.cpp \
    replacedialog.cpp \
    informationdialog.cpp

HEADERS  += mainwindow.h \
    document.h \
    namefiledialog.h \
    replacedialog.h \
    informationdialog.h

FORMS    += mainwindow.ui \
    namefiledialog.ui \
    replacedialog.ui \
    informationdialog.ui \
    fontdialog.ui
