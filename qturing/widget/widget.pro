#-------------------------------------------------
#
# Project created by QtCreator 2014-02-19T15:11:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = widget
TEMPLATE = app


SOURCES += main.cpp\
        turingmachine.cpp \
    ../../core/command.cpp \
    ../../core/parser.cpp \
    ../../core/program.cpp \
    ../../core/state.cpp \
    ../../core/tape.cpp

HEADERS  += turingmachine.h \
    ../../core/command.h \
    ../../core/parser.h \
    ../../core/program.h \
    ../../core/state.h \
    ../../core/tape.h

FORMS    += turingmachine.ui
