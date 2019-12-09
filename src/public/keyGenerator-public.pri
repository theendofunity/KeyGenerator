message("keyGenerator-public.pri")

LIBS_PATH = $$PWD/../../libs/

INCLUDEPATH += $$PWD

HEADERS += \
    $$PWD/DataModel.h \
    $$PWD/ConvertTools.h \

SOURCES += \
    $$PWD/DataModel.cpp \
    $$PWD/ConvertTools.cpp \

LIBS += -L$${LIBS_PATH}/cryptopp/ -lcryptopp
INCLUDEPATH += $${LIBS_PATH}/cryptopp/include
DEPENDPATH += $${LIBS_PATH}/cryptopp/include
