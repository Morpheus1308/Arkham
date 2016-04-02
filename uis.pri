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

win32 {
    CONFIG(release, debug|release): {
        LIBS += -L../model/src/release -lmodel
        PRE_TARGETDEPS += $$OUT_PWD/../model/src/release/model.lib
    }

    else:CONFIG(debug, debug|release): {
        LIBS += -L../model/src/debug -lmodel
        PRE_TARGETDEPS += $$OUT_PWD/../model/src/debug/model.lib
    }
}
