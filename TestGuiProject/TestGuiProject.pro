QT -= gui core

CONFIG += c++17

INCLUDEPATH += ./Controls

SOURCES += \
    Controls/Button.cpp \
    main.cpp


unix:!macx: LIBS += -L$$OUT_PWD/../GUI/ -lGUI

INCLUDEPATH += $$PWD/../GUI $$PWD/../GUI/BaseObjects \
               $$PWD/../GUI/Core/Font $$PWD/../GUI/Core/GObject \
               $$PWD/../GUI/Core/EventSystem

DEPENDPATH += $$PWD/../GUI $$PWD/../GUI/BaseObjects \
              $$PWD/../GUI/Core/Font $$PWD/../GUI/Core/GObject \
              $$PWD/../GUI/Core/EventSystem

unix:!macx: PRE_TARGETDEPS += $$OUT_PWD/../GUI/libGUI.a

unix:!macx: LIBS += -L$$OUT_PWD/../MI12864Display/ -lMI12864Display

INCLUDEPATH += $$PWD/../MI12864Display $$PWD/../MI12864Display/Buffers \
               $$PWD/../DisplayAbstraction
DEPENDPATH += $$PWD/../MI12864Display $$PWD/../MI12864Display/Buffers \
              $$PWD/../DisplayAbstraction

unix:!macx: PRE_TARGETDEPS += $$OUT_PWD/../MI12864Display/libMI12864Display.a

HEADERS += \
    Controls/Button.h
