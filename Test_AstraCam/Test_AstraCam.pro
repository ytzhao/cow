QT += core
QT -= gui

CONFIG += c++11

TARGET = Test_AstraCam
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    astra_reader/AstraReader.cpp \
    astra_calibration/AstraCalibration.cpp

INCLUDEPATH += /usr/include/openni2/
INCLUDEPATH += /home/moro/svn/Software/trunk/ThirdPartyLib/opencv-3.1.0/include/opencv2/

QMAKE_CXXFLAGS += -Wall
QMAKE_CXXFLAGS += -std=c++11
QMAKE_CXXFLAGS += -fexceptions
QMAKE_CXXFLAGS += -fPIC

QMAKE_LFLAGS += -L/home/moro/svn/Software/trunk/ThirdPartyLib/opencv-3.1.0/build/lib/

QMAKE_LFLAGS += -Wl,-rpath=/home/moro/svn/Software/trunk/ThirdPartyLib/boost/lib
QMAKE_LFLAGS += -Wl,-rpath=/home/moro/svn/Software/trunk/ThirdPartyLib/opencv-3.1.0/build/lib/

LIBS += -lboost_system
LIBS += -lopencv_core
LIBS += -lopencv_highgui
LIBS += -lopencv_imgproc
LIBS += -lopencv_imgcodecs
LIBS += -lopencv_calib3d
LIBS += -lOpenNI2

HEADERS += \
    astra_reader/AstraReader.h \
    astra_calibration/AstraCalibration.h
