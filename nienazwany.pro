QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addborrowdialog.cpp \
    main.cpp \
    mainwindow.cpp \
    addclientdialog.cpp \
    adddialog.cpp \
    addmoviedialog.cpp \
    editclientdialog.cpp \
    editmoviedialog.cpp \
    sortdialog.cpp

HEADERS += \
    addborrowdialog.h \
    mainwindow.h \
    addclientdialog.h \
    adddialog.h \
    addmoviedialog.h \
    editclientdialog.h \
    editmoviedialog.h \
    sortdialog.h

FORMS += \
    addborrowdialog.ui \
    mainwindow.ui \
    addclientdialog.ui \
    adddialog.ui \
    addmoviedialog.ui \
    editclientdialog.ui \
    editmoviedialog.ui \
    sortdialog.ui

TRANSLATIONS += \
    nienazwany_pl_PL.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
