QT       += core gui
QT       += charts
QT       += webenginewidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwidget.cpp \
    mappage.cpp \
    poi.cpp \
    poipage.cpp \
    predictpage.cpp \
    userpage.cpp \
    welcomedialog.cpp

HEADERS += \
    mainwidget.h \
    mappage.h \
    poi.h \
    poipage.h \
    predictpage.h \
    userpage.h \
    welcomedialog.h

FORMS += \
    mainwidget.ui \
    welcomedialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
