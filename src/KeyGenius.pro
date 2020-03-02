QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    KeyThread.cpp \
    inc/config.cpp \
    inc/cross/definition_mac.cpp \
    main.cpp \
    widget.cpp

HEADERS += \
    KeyThread.h \
    inc/config.h \
    inc/cross/cross.h \
    inc/cross/definition_mac.h \
    inc/cross/definition_win.h \
    widget.h

macx {
    LIBS += -framework Foundation
    LIBS += -framework AppKit

    OBJECTIVE_SOURCES += inc/cross/objectivec.mm
    HEADERS +=  inc/cross/objectivec.h
}

FORMS += \
    widget.ui

DISTFILES = res/KeyGenius.rc \
    res/Info.plist

RC_ICONS += "res/KeyGenius.ico"
RC_FILE += "res/KeyGenius.rc"

# Mac Config
ICON = "res/KeyGenius.icns"
QMAKE_INFO_PLIST = "res/Info.plist"

QDEP_DEPENDS += Skycoder42/QHotkey
!load(qdep):error("Failed to load qdep feature")

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res/Resource.qrc
