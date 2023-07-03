QT       += core gui
QT       += sql
QT       += charts

RC_ICONS = tmt.ico
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    clkmodule.cpp \
    clkpage.cpp \
    enroll.cpp \
    load.cpp \
    main.cpp \
    home.cpp \
    mainwindow.cpp \
    new_dlg.cpp \
    tmtclk.cpp \
    user.cpp \
    usercontroller.cpp \
    widget.cpp

HEADERS += \
    clkmodule.h \
    clkpage.h \
    enroll.h \
    home.h \
    load.h \
    mainwindow.h \
    new_dlg.h \
    tmtclk.h \
    user.h \
    usercontroller.h \
    widget.h

FORMS += \
    enroll.ui \
    home.ui \
    load.ui \
    mainwindow.ui \
    new_dlg.ui \
    tmtclk.ui \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    image.qrc
