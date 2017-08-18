#-------------------------------------------------
#
# Project created by QtCreator 2017-04-29T16:48:34
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = my_bms
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS
QTPLUGIN += QSQLMYSQL
# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        bms.cpp

HEADERS  += bms.h

INCLUDEPATH += "C:\Program Files\MySQL\MySQL Server 5.7\include"

LIBS += "C:\Program Files\MySQL\MySQL Server 5.7\lib\libmysql.lib"
FORMS    += bms.ui

DISTFILES += \
    6.png

RESOURCES += \
    image.qrc
