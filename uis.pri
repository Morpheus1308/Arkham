CONFIG += silent
CONFIG += c++11

win32 {

}

INCLUDEPATH += ../model/src

unix:!macx {
    LIBS += -L../model/src -lmodel
    PRE_TARGETDEPS += ../model/src/libmodel.a
}


macx {
    LIBS += -L../model/src -lmodel
    PRE_TARGETDEPS += ../model/src/libmodel.a
}

