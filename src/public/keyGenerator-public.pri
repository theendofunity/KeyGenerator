message("keyGenerator-public.pri")

LIBS_PATH = $$PWD/../../libs

INCLUDEPATH += $$PWD
INCLUDEPATH += $${LIBS_PATH}


HEADERS += \
    $${LIBS_PATH}/AES/qaesencryption.h \
    $$PWD/DataModel.h \

SOURCES += \
    $${LIBS_PATH}/AES/qaesencryption.cpp \
    $$PWD/DataModel.cpp \


