QT -= gui
QT += core

CONFIG -= qt
CONFIG += c++11 console
CONFIG -= app_bundle

TARGET = NCS
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += IOS_64
DEFINES += IOS_LINUX

QMAKE_LFLAGS += -fPIC

INCLUDEPATH  += /usr/local/include/
QMAKE_LFLAGS += -L/usr/local/lib
QMAKE_LFLAGS += -Wl,-rpath=/usr/local/lib
LIBS += -lmvnc

INCLUDEPATH  += /home/moro/svn/Software/trunk/ThirdPartyLib/opencv-3.1.0/include/
QMAKE_LFLAGS += -L/home/moro/svn/Software/trunk/ThirdPartyLib/opencv-3.1.0/build/lib
QMAKE_LFLAGS += -Wl,-rpath=/home/moro/svn/Software/trunk/ThirdPartyLib/opencv-3.1.0/build/lib
LIBS += -lopencv_core
LIBS += -lopencv_highgui
LIBS += -lopencv_imgproc
LIBS += -lopencv_videoio
LIBS += -lopencv_imgcodecs

SOURCES += main.cpp \
    NCS.cpp \
    util/fp16.c

HEADERS += \
    NCS.h \
    util/fp16.h \
    util/stb_image.h \
    util/stb_image_resize.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
