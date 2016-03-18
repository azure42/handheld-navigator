#-------------------------------------------------
#
# Project created by QtCreator 2016-03-10T21:32:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = demo6
TEMPLATE = app

PRECOMPILED_HEADER = stable.h
precompile_header:!isEmpty(PRECOMPILED_HEADER) {

      DEFINES += USING_DEBUG

}

SOURCES += \
    plotter.cpp \
    navdata.cpp \
    highway.cpp \
    main.cpp \
    key.cpp \
    content.cpp \
    steering.cpp \
    um220.cpp \
    qextserialbase.cpp \
    posix_qextserialport.cpp

HEADERS  += \
    navdata.h \
    plotter.h \
    steering.h \
    um220.h \
    highway.h \
    key.h \
    content.h \
    stable.h \
    qextserialbase.h \
    posix_qextserialport.h

FORMS    +=

RESOURCES += \
    src.qrc

OTHER_FILES +=
