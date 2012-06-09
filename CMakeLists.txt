#-------------------------------------------------
#
# Project created by QtCreator 2012-04-07T09:16:09
#
#-------------------------------------------------
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(CalibrationTool)

FIND_PACKAGE(Qt4 PATHS "D:/QtSDK" REQUIRED)
FIND_PACKAGE(OpenCV REQUIRED)

INCLUDE(${QT_USE_FILE})
ADD_DEFINITIONS(${QT_DEFINITIONS})

INCLUDE_DIRECTORIES(${QT_INCLUDE_DIR})

SET(cal_SOURCES main.cpp mainwindow.cpp touchylabel.cpp)
SET(cal_HEADERS mainwindow.h touchylabel.h)
SET(cal_FORMS mainwindow.ui)

QT4_WRAP_CPP(cal_HEADERS_MOC ${cal_HEADERS})
QT4_WRAP_UI(cal_FORMS_HEADERS ${cal_FORMS})


INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
ADD_EXECUTABLE(CalibrationTool ${cal_HEADERS_MOC}
                               ${cal_FORMS_HEADERS}
                               ${cal_SOURCES})

TARGET_LINK_LIBRARIES(CalibrationTool ${QT_LIBRARIES}
                                      ${OpenCV_LIBS})
