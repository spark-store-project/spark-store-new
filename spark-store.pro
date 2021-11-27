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
PKGCONFIG += dtkwidget glib-2.0 gdk-pixbuf-2.0 libnotify

# 禁止输出 qWarning / qDebug 信息
CONFIG(release, debug|release): DEFINES += QT_NO_WARNING_OUTPUT QT_NO_DEBUG_OUTPUT

SOURCES += \
        main.cpp \
        mainwindow-dtk.cpp \
        src/backend/sparkapi.cpp \
        src/widgets/downloadlistwidget.cpp \
        src/widgets/common/appitem.cpp \
        src/widgets/common/downloaditem.cpp \
        src/widgets/common/smoothlistwidget.cpp \
        src/widgets/common/smoothscrollbar.cpp \
        src/utils/httprequest.cpp \
        src/pages/applistpage.cpp \
        src/pages/homepage.cpp \
        src/backend/downloadworker.cpp \
    src/pages/appintopage.cpp \
    src/widgets/big_image.cpp \
    src/backend/image_show.cpp

HEADERS += \
        mainwindow-dtk.h \
        src/backend/sparkapi.h \
        src/widgets/downloadlistwidget.h \
        src/widgets/common/appitem.h \
        src/widgets/common/downloaditem.h \
        src/widgets/common/smoothlistwidget.h \
        src/widgets/common/smoothscrollbar.h \
        src/utils/httprequest.h \
        src/pages/applistpage.h \
        src/backend/downloadworker.h \
        src/pages/homepage.h \
    src/pages/appintopage.h \
    src/widgets/big_image.h \
    src/backend/image_show.h

FORMS += \
        mainwindow-dtk.ui \
        src/widgets/downloadlistwidget.ui \
        src/widgets/common/appitem.ui \
        src/widgets/common/downloaditem.ui \
        src/pages/applistpage.ui \
        src/pages/homepage.ui \
    src/pages/appintopage.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    assets/assets.qrc
