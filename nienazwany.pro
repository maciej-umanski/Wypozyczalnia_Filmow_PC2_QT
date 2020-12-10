QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addborrowdialog.cpp \
    editborrowdialog.cpp \
    main.cpp \
    mainwindow.cpp \
    addclientdialog.cpp \
    addmoviedialog.cpp \
    editclientdialog.cpp \
    editmoviedialog.cpp \
    others.cpp \
    sortdialog.cpp

HEADERS += \
    addborrowdialog.h \
    editborrowdialog.h \
    mainwindow.h \
    addclientdialog.h \
    addmoviedialog.h \
    editclientdialog.h \
    editmoviedialog.h \
    others.h \
    sortdialog.h

FORMS += \
    addborrowdialog.ui \
    editborrowdialog.ui \
    mainwindow.ui \
    addclientdialog.ui \
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
