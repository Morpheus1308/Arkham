TEMPLATE = lib
CONFIG += static silent
QT += network
TARGET = model
CONFIG += c++11

SOURCES +=  Model.cpp \
            Resident.cpp \
            Patient.cpp

HEADERS +=  Model.h \
            Resident.h \
            Patient.h

