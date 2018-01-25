QT += core
QT -= gui

TARGET  = AstraCam_Calib

CONFIG += c++11
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

QMAKE_CXXFLAGS += -Wall
QMAKE_CXXFLAGS += -std=c++11
QMAKE_CXXFLAGS += -fexceptions
QMAKE_CXXFLAGS += -fPIC

QMAKE_LFLAGS += -L$$PWD/../../../../../ThirdPartyLib/boost/lib
QMAKE_LFLAGS += -Wl,-rpath=../../../../../ThirdPartyLib/boost/lib
LIBS += -lboost_system

INCLUDEPATH += $$PWD/../../../../../ThirdPartyLib/opencv-3.1.0/include
QMAKE_LFLAGS += -L$$PWD/../../../../../ThirdPartyLib/opencv-3.1.0/build/lib
QMAKE_LFLAGS += -Wl,-rpath=../../../../../ThirdPartyLib/opencv-3.1.0/build/lib
LIBS += -lopencv_core
LIBS += -lopencv_highgui
LIBS += -lopencv_imgproc
LIBS += -lopencv_imgcodecs
LIBS += -lopencv_calib3d

INCLUDEPATH += $$PWD/../../../../../ThirdPartyLib/OpenNI/include
QMAKE_LFLAGS += -L$$PWD/../../../../../ThirdPartyLib/OpenNI/Redist
QMAKE_LFLAGS += -Wl,-rpath=../../../../../ThirdPartyLib/OpenNI/Redist
LIBS += -lOpenNI2

SOURCES += main.cpp \
    astra_reader/AstraReader.cpp \
    astra_calibration/AstraCalibration.cpp


HEADERS += \
    astra_reader/AstraReader.h \
    astra_calibration/AstraCalibration.h
