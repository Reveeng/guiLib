QT -= core gui

INCLUDEPATH += ../DisplayAbstraction ./Buffers ./

TEMPLATE = lib
CONFIG += staticlib c++17
QMAKE_CXXFLAGS += -O0 -g2



HEADERS += \
    ../DisplayAbstraction/AbstractDisplayManager.h \
    ../DisplayAbstraction/AbstractFontContainer.h \
    ../DisplayAbstraction/AbstractFrameBuffer.h \
    ../DisplayAbstraction/DataContainer.h \
    Buffers/Buffer.h \
    Buffers/FontData.h \
    Buffers/LabelBuffer.h \
    Buffers/font_small.h \
    DisplayManager.h \
    DisplayManagerDebug.h

SOURCES += \
    Buffers/Buffer.cpp \
    Buffers/FontData.cpp \
    Buffers/LabelBuffer.cpp \
    Buffers/font_small.cpp \
    DisplayManager.cpp \
    DisplayManagerDebug.cpp

