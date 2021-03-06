#-------------------------------------------------
#
# Project created by QtCreator 2021-10-29T16:58:36
#
#-------------------------------------------------

QT       += core gui network concurrent

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
PKGCONFIG += dtkcore dtkgui dtkwidget libnotify

# Disable qWarning / qDebug output in Release
CONFIG(release, debug|release): DEFINES += QT_NO_WARNING_OUTPUT QT_NO_DEBUG_OUTPUT

SOURCES += \
        main.cpp \
        mainwindow-dtk.cpp \
        backend/sparkapi.cpp \
        widgets/downloadlistwidget.cpp \
        widgets/common/appitem.cpp \
        widgets/common/downloaditem.cpp \
        widgets/common/smoothlistwidget.cpp \
        widgets/common/smoothscrollbar.cpp \
        utils/httprequest.cpp \
        pages/applistpage.cpp \
        pages/homepage.cpp \
        backend/downloadworker.cpp \
        pages/appintopage.cpp \
        widgets/big_image.cpp \
        backend/image_show.cpp

HEADERS += \
        mainwindow-dtk.h \
        backend/sparkapi.h \
        widgets/downloadlistwidget.h \
        widgets/common/appitem.h \
        widgets/common/downloaditem.h \
        widgets/common/smoothlistwidget.h \
        widgets/common/smoothscrollbar.h \
        utils/httprequest.h \
        pages/applistpage.h \
        backend/downloadworker.h \
        pages/homepage.h \
        pages/appintopage.h \
        widgets/big_image.h \
        backend/image_show.h

FORMS += \
        mainwindow-dtk.ui \
        widgets/downloadlistwidget.ui \
        widgets/common/appitem.ui \
        widgets/common/downloaditem.ui \
        pages/applistpage.ui \
        pages/homepage.ui \
        pages/appintopage.ui

RESOURCES += \
        assets/assets.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/durapps/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
