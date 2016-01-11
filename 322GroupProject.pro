#-------------------------------------------------
#
# Project created by QtCreator 2015-12-03T15:00:33
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 322GroupProject
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp\
        book.cpp\
        user.cpp\
        invite.cpp\
        review.cpp \
    readbook.cpp

HEADERS  += mainwindow.h\
        book.h\
        user.h\
        invite.h \
    review.h \
    readbook.h

FORMS    += mainwindow.ui \
    readbook.ui
