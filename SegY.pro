TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    SegYIOUtils.cpp \
    SegYTraceReader.cpp \
    SegYReader.cpp \
    SegYTraceWriter.cpp \
    SegYWriter.cpp

HEADERS += \
    SegYIOUtils.h \
    SegYTraceReader.h \
    SegYReader.h \
    SegYTraceWriter.h \
    SegYWriter.h \
    SegYBytesPositions.h \
    SegYCommon.h
