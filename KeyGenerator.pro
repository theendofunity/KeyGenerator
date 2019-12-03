QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

PROJECT_ROOT = $${_PRO_FILE_PWD_}

INCLUDEPATH += $${PROJECT_ROOT}/src
INCLUDEPATH += $${PROJECT_ROOT}/libs

include($${PROJECT_ROOT}/src/decoder/decoder.pri)

SOURCES += \
    src/AccessKeyGenerator.cpp \
    src/ConvertTools.cpp \
    src/DataModel.cpp \
    src/EncryptKeyGenerator.cpp \
    src/main.cpp \
    src/MainWindow.cpp

HEADERS += \
    src/AccessKeyGenerator.h \
    src/ConvertTools.h \
    src/DataModel.h \
    src/EncryptKeyGenerator.h \
    src/MainWindow.h


unix:!macx: LIBS += -L$$PWD/libs/cryptopp -lcryptopp

INCLUDEPATH += $$PWD/libs/cryptopp
DEPENDPATH += $$PWD/libs/cryptopp
