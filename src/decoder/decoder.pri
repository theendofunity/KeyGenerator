message("decoder.pri")

include($$PWD/../public/keyGenerator-public.pri)

INCLUDEPATH += $$PWD
INCLUDEPATH += $$PWD/../

HEADERS += \
    $$PWD/AccessController.h \
    $$PWD/Decoder.h \

SOURCES += \
    $$PWD/AccessController.cpp \
    $$PWD/Decoder.cpp \

