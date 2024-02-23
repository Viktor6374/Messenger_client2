QT       += core gui
QT += network
CONFIG += console
CONFIG -= app_bundle
#dbghelp
LIBS += dbghelp.lib


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Entities/currentuser.cpp \
    Entities/history_messaging.cpp \
    Entities/interlocutor.cpp \
    Entities/message.cpp \
    Entities/user.cpp \
    Threads/response_listener.cpp \
    Threads/response_listener_worker.cpp \
    Threads/response_processing.cpp \
    connections/initializer.cpp \
    connections/requestfactory.cpp \
    connections/responseparser.cpp \
    dbgcrash.cpp \
    main.cpp \
    services/service.cpp \
    windows/add_new_chat.cpp \
    windows/authorization.cpp \
    windows/mainwindow.cpp

HEADERS += \
    Entities/currentuser.h \
    Entities/history_messaging.h \
    Entities/interlocutor.h \
    Entities/message.h \
    Entities/user.h \
    Threads/response_listener.h \
    Threads/response_listener_worker.h \
    Threads/response_processing.h \
    connections/initializer.h \
    connections/requestfactory.h \
    connections/responseparser.h \
    dbgcrash.h \
    services/service.h \
    windows/add_new_chat.h \
    windows/authorization.h \
    windows/mainwindow.h

FORMS += \
    add_new_chat.ui \
    authorization.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=
