QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
CONFIG -= app_bundle

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    tablemodel.cpp

HEADERS += \
    mainwindow.h \
    tablemodel.h

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
