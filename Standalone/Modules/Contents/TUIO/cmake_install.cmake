# Install script for directory: /Users/kristian/Dropbox/github/Polycode/Modules/Contents/TUIO

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/Users/kristian/Dropbox/github/Polycode/Release/Darwin/Framework/")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "RelWithDebInfo")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Modules/include" TYPE FILE FILES
    "/Users/kristian/Dropbox/github/Polycode/Modules/Contents/TUIO/Include/TuioClient.h"
    "/Users/kristian/Dropbox/github/Polycode/Modules/Contents/TUIO/Include/TuioContainer.h"
    "/Users/kristian/Dropbox/github/Polycode/Modules/Contents/TUIO/Include/TuioCursor.h"
    "/Users/kristian/Dropbox/github/Polycode/Modules/Contents/TUIO/Include/TUIOInputModule.h"
    "/Users/kristian/Dropbox/github/Polycode/Modules/Contents/TUIO/Include/TuioListener.h"
    "/Users/kristian/Dropbox/github/Polycode/Modules/Contents/TUIO/Include/TuioObject.h"
    "/Users/kristian/Dropbox/github/Polycode/Modules/Contents/TUIO/Include/TuioPoint.h"
    "/Users/kristian/Dropbox/github/Polycode/Modules/Contents/TUIO/Include/TuioServer.h"
    "/Users/kristian/Dropbox/github/Polycode/Modules/Contents/TUIO/Include/TuioTime.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Modules/include" TYPE DIRECTORY FILES "/Users/kristian/Dropbox/github/Polycode/Modules/Contents/TUIO/Include/ip")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Modules/include" TYPE DIRECTORY FILES "/Users/kristian/Dropbox/github/Polycode/Modules/Contents/TUIO/Include/osc")
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Modules/lib" TYPE STATIC_LIBRARY FILES "/Users/kristian/Dropbox/github/Polycode/Standalone/Modules/Contents/TUIO/libPolycodeTUIO.a")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/Modules/lib/libPolycodeTUIO.a" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/Modules/lib/libPolycodeTUIO.a")
    EXECUTE_PROCESS(COMMAND "/usr/bin/ranlib" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/Modules/lib/libPolycodeTUIO.a")
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

