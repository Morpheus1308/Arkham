QT += testlib network

TEMPLATE = app

INCLUDEPATH += ../../src/


SOURCES += ../MockResident.cpp
HEADERS += ../MockResident.h

unix:!macx {
    LIBS += -L../../src -lmodel
    PRE_TARGETDEPS += ../../src/libmodel.a
}

macx {
    LIBS += -L../../src -lmodel
    PRE_TARGETDEPS += ../../src/libmodel.a
}


CONFIG += c++11
CONFIG += silent
CONFIG += build
CONFIG += testcase


