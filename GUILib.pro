TEMPLATE = subdirs

SUBDIRS += \
    GUI \
    MI12864Display \
    TestGuiProject

GUI.depends = MI12864Display

TestGuiProject.depends = MI12864Display GUI

unix:!macx: LIBS += -L$$OUT_PWD/MI12864Display/ -lMI12864Display

INCLUDEPATH += $$PWD/MI12864Display
DEPENDPATH += $$PWD/MI12864Display

unix:!macx: PRE_TARGETDEPS += $$OUT_PWD/MI12864Display/libMI12864Display.a
