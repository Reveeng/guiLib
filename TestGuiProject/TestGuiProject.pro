QT -= gui core

CONFIG += c++17

INCLUDEPATH += ./Controls ./Icons

SOURCES += \
    Controls/Button.cpp \
    Controls/Menu.cpp \
    Controls/MenuButton.cpp \
    Controls/PlainText.cpp \
    Icons/CheckIcon.cpp \
    Icons/DownTriangle.cpp \
    Icons/UpTriangle.cpp \
    main.cpp


HEADERS += \
    Controls/Button.h \
    Controls/Menu.h \
    Controls/MenuButton.h \
    Controls/PlainText.h \
    Icons/CheckIcon.h \
    Icons/DownTriangle.h \
    Icons/UpTriangle.h

unix:!macx: LIBS += -L$$OUT_PWD/../GUI/ -lGUI

INCLUDEPATH += $$PWD/../GUI $$PWD/../GUI/BaseObjects \
               $$PWD/../GUI/Core/Font $$PWD/../GUI/Core/GObject \
               $$PWD/../GUI/Core/EventSystem $$PWD/../GUI/Core/GObject/AbstractClass

DEPENDPATH += $$PWD/../GUI $$PWD/../GUI/BaseObjects \
              $$PWD/../GUI/Core/Font $$PWD/../GUI/Core/GObject \
              $$PWD/../GUI/Core/EventSystem $$PWD/../GUI/Core/GObject/AbstractClass

unix:!macx: PRE_TARGETDEPS += $$OUT_PWD/../GUI/libGUI.a

unix:!macx: LIBS += -L$$OUT_PWD/../MI12864Display/ -lMI12864Display

INCLUDEPATH += $$PWD/../MI12864Display $$PWD/../MI12864Display/Buffers \
               $$PWD/../DisplayAbstraction
DEPENDPATH += $$PWD/../MI12864Display $$PWD/../MI12864Display/Buffers \
              $$PWD/../DisplayAbstraction

unix:!macx: PRE_TARGETDEPS += $$OUT_PWD/../MI12864Display/libMI12864Display.a


