TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += ./Display ./Display/Abstraction ./Display/Buffers \
               ./Display/Fonts ./EventSystem ./GUI ./GUI/Core \
               ./GUI/BaseObjects

HEADERS += \
    Display/Abstraction/AbstractDisplayManager.h \
    Display/Abstraction/AbstractFontContainer.h \
    Display/Abstraction/AbstractFrameBuffer.h \
    Display/Abstraction/DataContainer.h \
    Display/Backends/CLI/DisplayManager.h \
    Display/Buffers/MI12864/Buffer.h \
    Display/Buffers/MI12864/LabelBuffer.h \
    Display/Fonts/FontManager.h \
    Display/Fonts/MI12864/FontData.h \
    Display/Fonts/MI12864/font_small.h \
    EventSystem/Event.h \
    EventSystem/EventLoop.h \
    EventSystem/EventQueue.h \
    GUI/BaseObjects/Label.h \
    GUI/BaseObjects/MainWindow.h \
    GUI/BaseObjects/Rectangle.h \
    GUI/Core/GObject.h \
    GUI/Core/GObjectBase.h \
    GUI/Core/GObjectRectangle.h \
    GUI/Core/GTimer.h \
    GUI/Core/MainEventLoop.h


SOURCES += \
    Display/Backends/CLI/DisplayManager.cpp \
    Display/Buffers/MI12864/Buffer.cpp \
    Display/Buffers/MI12864/LabelBuffer.cpp \
    Display/Fonts/FontManager.cpp \
    Display/Fonts/MI12864/font_small.cpp \
    EventSystem/Event.cpp \
    EventSystem/EventLoop.cpp \
    EventSystem/EventQueue.cpp \
    GUI/BaseObjects/Label.cpp \
    GUI/BaseObjects/MainWindow.cpp \
    GUI/BaseObjects/Rectangle.cpp \
    GUI/Core/GObject.cpp \
    GUI/Core/GObjectBase.cpp \
    GUI/Core/GObjectRectangle.cpp \
    GUI/Core/GTimer.cpp \
    GUI/Core/MainEventLoop.cpp \
    main.cpp
