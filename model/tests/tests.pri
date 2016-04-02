QT += testlib network core

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

win32
{
    CONFIG(release, debug|release): {
        LIBS += -L../../src/release -lmodel
        PRE_TARGETDEPS += $$OUT_PWD/../../src/release/model.lib
    }
    else:CONFIG(debug, debug|release): {
        LIBS += -L../../src/debug -lmodel
        PRE_TARGETDEPS += $$OUT_PWD/../../src/debug/model.lib
    }
}

CONFIG += c++11
CONFIG += build
CONFIG += testcase


