QT -= gui

TEMPLATE = lib
DEFINES += AGIFALIB_LIBRARY

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
    agifa_array_pointers.cpp \
    agifa_motor.cpp \
    agifa_node.cpp \
    agifa_sensor.cpp \
    agifa_system.cpp \
    agifalib.cpp

HEADERS += \
    agifa_array.h \
    agifa_array_pointers.h \
    agifa_motor.h \
    agifa_node.h \
    agifa_sensor.h \
    agifa_system.h \
    agifadef.h \
    agifalib_global.h \
    agifalib.h

TRANSLATIONS += \
    agifalib_ru_RU.ts

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target
