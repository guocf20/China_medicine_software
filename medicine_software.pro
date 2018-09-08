#-------------------------------------------------
#
# Project created by QtCreator 2018-08-23T20:27:03
#
#-------------------------------------------------

QT       += core gui widgets sql

RC_ICONS = icon.ico

TARGET = medicine_software
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    login_dialog.cpp \
    record_form.cpp \
    change_pwd_dialog.cpp \
    search_form.cpp \
    table_with_database.cpp \
    add_medicine_entry.cpp \
    del_medicine_entry.cpp \
    comm_window.cpp

HEADERS += \
        mainwindow.h \
    login_dialog.h \
    com_define.h \
    record_form.h \
    change_pwd_dialog.h \
    search_form.h \
    table_with_database.h \
    add_medicine_entry.h \
    del_medicine_entry.h \
    comm_window.h

FORMS += \
        mainwindow.ui \
    login_dialog.ui \
    record_form.ui \
    change_pwd_dialog.ui \
    search_form.ui \
    add_medicine_entry.ui \
    del_medicine_entry.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

SUBDIRS += \
    medicine_software.pro

DISTFILES +=

RESOURCES += \
    images.qrc
