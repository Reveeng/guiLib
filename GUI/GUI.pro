QT -= core gui

INCLUDEPATH += ../DisplayAbstraction ./Core/EventSystem ./Core/Font \
               ./Core/GObject ./BaseObjects

TEMPLATE = lib
CONFIG += staticlib c++17
QMAKE_CXXFLAGS += -O0 -g2


HEADERS += \
    ../DisplayAbstraction/AbstractDisplayManager.h \
    ../DisplayAbstraction/AbstractFontContainer.h \
    ../DisplayAbstraction/AbstractFrameBuffer.h \
    ../DisplayAbstraction/DataContainer.h \
    BaseObjects/Label.h \
    BaseObjects/MainWindow.h \
    BaseObjects/Rectangle.h \
    Core/EventSystem/Event.h \
    Core/EventSystem/EventLoop.h \
    Core/EventSystem/EventQueue.h \
    Core/EventSystem/MainEventLoop.h \
    Core/Font/FontManager.h \
    Core/GObject/GObject.h \
    Core/GObject/GObjectAnchors.h \
    Core/GObject/GObjectBase.h \
    Core/GObject/GObjectRectangle.h \
    Core/GObject/GTimer.h

SOURCES += \
    BaseObjects/Label.cpp \
    BaseObjects/MainWindow.cpp \
    BaseObjects/Rectangle.cpp \
    Core/EventSystem/Event.cpp \
    Core/EventSystem/EventLoop.cpp \
    Core/EventSystem/EventQueue.cpp \
    Core/EventSystem/MainEventLoop.cpp \
    Core/Font/FontManager.cpp \
    Core/GObject/GObject.cpp \
    Core/GObject/GObjectAnchors.cpp \
    Core/GObject/GObjectBase.cpp \
    Core/GObject/GObjectRectangle.cpp \
    Core/GObject/GTimer.cpp


unix:!macx: LIBS += -L$$OUT_PWD/../MI12864Display/ -lMI12864Display

INCLUDEPATH += $$PWD/../MI12864Display $$PWD/../MI12864Display/Buffers
DEPENDPATH += $$PWD/../MI12864Display $$PWD/../MI12864Display/Buffers

unix:!macx: PRE_TARGETDEPS += $$OUT_PWD/../MI12864Display/libMI12864Display.a
