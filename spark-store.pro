#-------------------------------------------------
#
# Project created by QtCreator 2019-06-30T12:53:03
#
#-------------------------------------------------

QT       += core gui network concurrent webenginewidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = spark-store
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

DEFINES += QT_APP_DEBUG

CONFIG += c++11 link_pkgconfig
PKGCONFIG += dtkwidget glib-2.0 gdk-pixbuf-2.0 libnotify

# 禁止输出 qWarning / qDebug 信息
CONFIG(release, debug|release): DEFINES += QT_NO_WARNING_OUTPUT QT_NO_DEBUG_OUTPUT

SOURCES += \
        main.cpp \
        mainwindow-dtk.cpp \
        src/backend/sparkapi.cpp

HEADERS += \
        mainwindow-dtk.h \
        src/backend/sparkapi.h

FORMS += \
        mainwindow-dtk.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    assets/assets.qrc