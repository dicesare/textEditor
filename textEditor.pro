QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/filemanagement/filemanager.cpp \
    src/controller/controllereditor.cpp \
    src/filemanagement/pathglobal.cpp \
    src/view/customtextedit.cpp \
    src/view/mainwindow.cpp \
    src/main.cpp \
    src/view/tabwidgeteditor.cpp

HEADERS += \
    src/filemanagement/filemanager.h \
    src/controller/controllereditor.h \
    src/filemanagement/pathglobal.h \
    src/view/customtextedit.h \
    src/view/mainwindow.h \
    src/view/tabwidgeteditor.h

FORMS += \
    mainwindow.ui

INCLUDEPATH += $$PWD/src/view

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
