#-------------------------------------------------
#
# Project created by QtCreator 2017-12-09T13:19:42
#
#-------------------------------------------------

QT       += core gui
QT       += opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DisplayTree
TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
#CONFIG -= qt

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        DisplayTree.cpp \
        DecisionTree.cpp \
        main.cpp

HEADERS += \
<<<<<<< HEAD
        #DisplayTree.h \
        #decisiontree.h \
        temp.h
=======
        DisplayTree.h \
    DecisionTree.h
>>>>>>> 7962c4ce5dae8557862897765da89eb23871b89f

FORMS += \
        DisplayTree.ui

DISTFILES += \
    iris.data
