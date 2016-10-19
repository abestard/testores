#-------------------------------------------------
#
# Project created by QtCreator 2016-06-30T22:56:10
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = proyecto
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ma.cpp \
    fichero.cpp \
    matrix.cpp \
    mb.cpp \
    md.cpp \
    generar_md.cpp \
    lex.cpp \
    ma_md.cpp \
    teoria_de_testores.cpp \
    bits.cpp \
    bt.cpp \
    mythread.cpp

HEADERS  += mainwindow.h \
    ma.h \
    fichero.h \
    matrix.h \
    mb.h \
    md.h \
    generar_md.h \
    lex.h \
    ma_md.h \
    teoria_de_testores.h \
    bits.h \
    bt.h \
    mythread.h

FORMS    += mainwindow.ui \
    ma.ui \
    mb.ui \
    md.ui \
    generar_md.ui \
    lex.ui \
    ma_md.ui \
    bt.ui
