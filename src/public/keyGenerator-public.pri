message("keyGenerator-public.pri")

LIBS_PATH = $$PWD/../../libs

INCLUDEPATH += $$PWD
INCLUDEPATH += $${LIBS_PATH}


HEADERS += \
    $$PWD/AccessKeyDataModel.h \
    $${LIBS_PATH}/AES/qaesencryption.h \

SOURCES += \
    $$PWD/AccessKeyDataModel.cpp \
    $${LIBS_PATH}/AES/qaesencryption.cpp \


