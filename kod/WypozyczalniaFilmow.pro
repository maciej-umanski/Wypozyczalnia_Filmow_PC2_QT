QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    addborrowdialog.cpp \
    addclientdialog.cpp \
    addmoviedialog.cpp \
    editborrowdialog.cpp \
    editclientdialog.cpp \
    editmoviedialog.cpp \
    setpenaltydialog.cpp

HEADERS += \
    mainwindow.h \
    addborrowdialog.h \
    addclientdialog.h \
    addmoviedialog.h \
    editborrowdialog.h \
    editclientdialog.h \
    editmoviedialog.h \
    setpenaltydialog.h

FORMS += \
    mainwindow.ui \
    addborrowdialog.ui \
    addclientdialog.ui \
    addmoviedialog.ui \
    editborrowdialog.ui \
    editclientdialog.ui \
    editmoviedialog.ui \
    setpenaltydialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
