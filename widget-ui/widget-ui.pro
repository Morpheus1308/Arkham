TEMPLATE = app
TARGET = widget-ui
INCLUDEPATH += . ../

SOURCES += main.cpp

win32 {

}

unix:!macx {
    LIBS += -L../model -lmodel
    PRE_TARGETDEPS += ../model/libmodel.a
}


macx {
    LIBS += -L../model -lmodel
    PRE_TARGETDEPS += ../model/libmodel.a
}

