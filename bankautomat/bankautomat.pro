QT       += core gui
QT += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    consolecreditdebit.cpp \
    consolemain.cpp \
    consolemuusumma.cpp \
    consolenosto.cpp \
    consolepassword.cpp \
    consolesaldo.cpp \
    consoletilitapahtumat.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    consolecreditdebit.h \
    consolemain.h \
    consolemuusumma.h \
    consolenosto.h \
    consolepassword.h \
    consolesaldo.h \
    consoletilitapahtumat.h \
    mainwindow.h

FORMS += \
    consolecreditdebit.ui \
    consolemain.ui \
    consolemuusumma.ui \
    consolenosto.ui \
    consolepassword.ui \
    consolesaldo.ui \
    consoletilitapahtumat.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
