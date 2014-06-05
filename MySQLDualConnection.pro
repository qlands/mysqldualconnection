#-------------------------------------------------
#
# Project created by QtCreator 2014-06-03T13:41:31
#
#-------------------------------------------------

QT       += core sql

QT       -= gui

TARGET = mysqldualconnection
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

unix:INCLUDEPATH += /usr/include/mysql
unix:LIBS += -L/lib64 -L/usr/lib64 \
    -lcrypt \
    -laio \    
    -ldl \
    -lrt \
    -lz -lmysqld

SOURCES += main.cpp \
    mydbconn.cpp \
    embdriver.cpp

HEADERS += \
    embdriver.h \
    mydbconn.h
