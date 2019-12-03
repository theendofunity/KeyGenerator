PRI_PATH = $${PROJECT_ROOT}/libs/cryptopp

INCLUDEPATH += $${PRI_PATH}

HEADERS += \
    $$PWD/config.h \
    $$PWD/cryptlib.h \
    $$PWD/files.h \
    $$PWD/hex.h \
    $$PWD/osrng.h \
    $$PWD/pch.h \
    $$PWD/rabbit.h \
    $$PWD/secblock.h \
    $$PWD/stdcpp.h \
    $$PWD/strciphr.h \
    $$PWD/trap.h

SOURCES += \
    $$PWD/cryptlib.cpp \
    $$PWD/files.cpp \
    $$PWD/hex.cpp \
    $$PWD/osrng.cpp \
    $$PWD/pch.cpp \
    $$PWD/rabbit.cpp \
    $$PWD/strciphr.cpp
