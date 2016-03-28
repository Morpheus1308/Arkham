include(../uis.pri)

QT += widgets
TEMPLATE = app
TARGET = widget-ui
INCLUDEPATH += . ../model/src

SOURCES += main.cpp \
    MainWindow.cpp \
    LoginDialog.cpp

FORMS += \
    MainWindow.ui \
    LoginDialog.ui

HEADERS += \
    MainWindow.h \
    LoginDialog.h


