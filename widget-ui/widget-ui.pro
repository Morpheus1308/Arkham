include(../uis.pri)

QT += widgets
TEMPLATE = app
TARGET = widget-ui
INCLUDEPATH += . ../model/src

SOURCES += main.cpp \
    MainWindow.cpp \
    LoginDialog.cpp \
    CreateResidentDialog.cpp

FORMS += \
    MainWindow.ui \
    LoginDialog.ui \
    CreateResidentDialog.ui

HEADERS += \
    MainWindow.h \
    LoginDialog.h \
    CreateResidentDialog.h

RESOURCES += \
    icons.qrc


