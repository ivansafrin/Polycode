# Install script for directory: /Users/kristian/Dropbox/github/Polycode/Core/Contents

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
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Core/include" TYPE FILE FILES
    "/Users/kristian/Dropbox/github/Polycode/Core/Contents/Include/OSBasics.h"
    "/Users/kristian/Dropbox/github/Polycode/Core/Contents/Include/PolyBezierCurve.h"
    "/Users/kristian/Dropbox/github/Polycode/Core/Contents/Include/PolyBone.h"
    "/Users/kristian/Dropbox/github/Polycode/Core/Contents/Include/PolyCamera.h"
    "/Users/kristian/Dropbox/github/Polycode/Core/Contents/Include/Polycode.h"
    "/Users/kristian/Dropbox/github/Polycode/Core/Contents/Include/PolyColor.h"
    "/Users/kristian/Dropbox/github/Polycode/Core/Contents/Include/PolyConfig.h"
    "/Users/kristian/Dropbox/github/Polycode/Core/Contents/Include/PolyCore.h"
    "/Users/kristian/Dropbox/github/Polycode/Core/Contents/Include/PolyCoreInput.h"
    "/Users/kristian/Dropbox/github/Polycode/Core/Contents/Include/PolyCoreServices.h"
    "/Users/kristian/Dropbox/github/Polycode/Core/Contents/Include/PolyCubemap.h"
    "/Users/kristian/Dropbox/github/Polycode/Core/Contents/Include/PolyData.h"
    "/Users/kristian/Dropbox/github/Polycode/Core/Contents/Include/PolyEntity.h"
    "/Users/kristian/Dropbox/github/Polycode/Core/Contents/Include/PolyEventDispatcher.h"
    "/Users/kristian/Dropbox/github/Polycode/Core/Contents/Include/PolyEvent.h"
    "/Users/kristian/Dropbox/github/Polycode/Core/Contents/Include/PolyEventHandler.h"
    "/Users/kristian/Dropbox/github/Polycode/Core/Contents/Include/PolyFixedShader.h"
    "/Users/kristian/Dropbox/github/Polycode/Core/Contents/Include/PolyFont.h"
    "/Users/kristian/Dropbox/github/Polycode/Core/Contents/Include/PolyFontManager.h"
    "/Users/kristian/Dropbox/github/Polycode/Core/Contents/Include/PolyGLCubemap.h"
    "/Users/kristian/Dropbox/github/Polycode/Core/Contents/Include/PolyGLHeaders.h"
    "/Users/kristian/Dropbox/github/Polycode/Core/Contents/Include/PolyGlobals.h"
    "/Users/kristian/Dropbox/github/Polycode/Core/Contents/Include/PolyGLRenderer.h"
    "/Users/kristian/Dropbox/github/Polycode/Core/Contents/Include/PolyGLSLProgram.h"
    "/Users/kristian/Dropbox/github/Polycode/Core/Contents/Include/PolyGLSLShader.h"
    "/Users/kristian/Dropbox/github/Polycode/Core/Contents/Include/PolyGLSLShaderModule.h"
    "/Users/kristian/Dropbox/github/Polycode/Core/Contents/Include/PolyGLTexture.h"
    "/Users/kristian/Dropbox/github/Polycode/Core/Contents/Include/PolyGLVertexBuffer.h"
    "/Users/kristian/Dropbox/github/Polycode/Core/Contents/Include/PolyImage.h"
    "/Users/kristian/Dropbox/github/Polycode/Core/Contents/Include/PolyInputEvent.h"
    "/Users/kristian/Dropbox/github/Polycode/Core/Contents/Include/PolyInputKeys.h"
    "/Users/kristian/Dropbox/github/Polycode/Core/Contents/Include/PolyLabel.h"
    "/Users/kristian/Dropbox/github/Polycode/Core/Contents/Include/PolyLogger.h"
    "/Users/kristian/Dropbox/github/Polycode/Core/Contents/Include/PolyMaterial.h"
    "/Users/kristian/Dropbox/github/Polycode/Core/Contents/Include/PolyMaterialManager.h"
    "/Users/kristian/Dropbox/github/Polycode/Core/Contents/Include/PolyMatrix4.h"
    "/Users/kristian/Dropbox/github/Polycode/Core/Contents/Include/PolyMesh.h"
    "/Users/kristian/Dropbox/github/Polycode/Core/Contents/Include/PolyModule.h"
    "/Users/kristian/Dropbox/github/Polycode/Core/Contents/Include/PolyObject.h"
    "/Users/kristian/Dropbox/github/Polycode/Core/Contents/Include/PolyParticleEmitter.h"
    "/Users/kristian/Dropbox/github/Polycode/Core/Contents/Include/PolyParticle.h"
    "/Users/kristian/Dropbox/github/Polycode/Core/Contents/Include/PolyPerlin.h"
    "/Users/kristian/Dropbox/github/Polycode/Core/Contents/Include/PolyPolygon.h"
    "/Users/kristian/Dropbox/github/Polycode/Core/Contents/Include/PolyQuaternionCurve.h"
    "/Users/kristian/Dropbox/github/Polycode/Core/Contents/Include/PolyQuaternion.h"
    "/Users/kristian/Dropbox/github/Polycode/Core/Contents/Include/PolyRectangle.h"
    "/Users/kristian/Dropbox/github/Polycode/Core/Contents/Include/PolyRenderer.h"
    "/Users/kristian/Dropbox/github/Polycode/Core/Contents/Include/PolyResource.h"
    "/Users/kristian/Dropbox/github/Polycode/Core/Contents/Include/PolyResourceManager.h"
    "/Users/kristian/Dropbox/github/Polycode/Core/Contents/Include/PolySceneEntity.h"
    "/Users/kristian/Dropbox/github/Polycode/Core/Contents/Include/PolyScene.h"
    "/Users/kristian/Dropbox/github/Polycode/Core/Contents/Include/PolySceneLabel.h"
    "/Users/kristian/Dropbox/github/Polycode/Core/Contents/Include/PolySceneLight.h"
    "/Users/kristian/Dropbox/github/Polycode/Core/Contents/Include/PolySceneLine.h"
    "/Users/kristian/Dropbox/github/Polycode/Core/Contents/Include/PolySceneManager.h"
    "/Users/kristian/Dropbox/github/Polycode/Core/Contents/Include/PolySceneMesh.h"
    "/Users/kristian/Dropbox/github/Polycode/Core/Contents/Include/PolyScenePrimitive.h"
    "/Users/kristian/Dropbox/github/Polycode/Core/Contents/Include/PolySceneRenderTexture.h"
    "/Users/kristian/Dropbox/github/Polycode/Core/Contents/Include/PolySceneSound.h"
    "/Users/kristian/Dropbox/github/Polycode/Core/Contents/Include/PolyScreenEntity.h"
    "/Users/kristian/Dropbox/github/Polycode/Core/Contents/Include/PolyScreenEvent.h"
    "/Users/kristian/Dropbox/github/Polycode/Core/Contents/Include/PolyScreen.h"
    "/Users/kristian/Dropbox/github/Polycode/Core/Contents/Include/PolyScreenImage.h"
    "/Users/kristian/Dropbox/github/Polycode/Core/Contents/Include/PolyScreenLabel.h"
    "/Users/kristian/Dropbox/github/Polycode/Core/Contents/Include/PolyScreenLine.h"
    "/Users/kristian/Dropbox/github/Polycode/Core/Contents/Include/PolyScreenManager.h"
    "/Users/kristian/Dropbox/github/Polycode/Core/Contents/Include/PolyScreenMesh.h"
    "/Users/kristian/Dropbox/github/Polycode/Core/Contents/Include/PolyScreenShape.h"
    "/Users/kristian/Dropbox/github/Polycode/Core/Contents/Include/PolyScreenSound.h"
    "/Users/kristian/Dropbox/github/Polycode/Core/Contents/Include/PolyScreenSprite.h"
    "/Users/kristian/Dropbox/github/Polycode/Core/Contents/Include/PolyScreenEntityInstance.h"
    "/Users/kristian/Dropbox/github/Polycode/Core/Contents/Include/PolyShader.h"
    "/Users/kristian/Dropbox/github/Polycode/Core/Contents/Include/PolySkeleton.h"
    "/Users/kristian/Dropbox/github/Polycode/Core/Contents/Include/PolySound.h"
    "/Users/kristian/Dropbox/github/Polycode/Core/Contents/Include/PolySoundManager.h"
    "/Users/kristian/Dropbox/github/Polycode/Core/Contents/Include/PolyString.h"
    "/Users/kristian/Dropbox/github/Polycode/Core/Contents/Include/PolyTexture.h"
    "/Users/kristian/Dropbox/github/Polycode/Core/Contents/Include/PolyThreaded.h"
    "/Users/kristian/Dropbox/github/Polycode/Core/Contents/Include/PolyTimer.h"
    "/Users/kristian/Dropbox/github/Polycode/Core/Contents/Include/PolyTimerManager.h"
    "/Users/kristian/Dropbox/github/Polycode/Core/Contents/Include/PolyTween.h"
    "/Users/kristian/Dropbox/github/Polycode/Core/Contents/Include/PolyTweenManager.h"
    "/Users/kristian/Dropbox/github/Polycode/Core/Contents/Include/PolyVector2.h"
    "/Users/kristian/Dropbox/github/Polycode/Core/Contents/Include/PolyVector3.h"
    "/Users/kristian/Dropbox/github/Polycode/Core/Contents/Include/PolyVertex.h"
    "/Users/kristian/Dropbox/github/Polycode/Core/Contents/Include/tinystr.h"
    "/Users/kristian/Dropbox/github/Polycode/Core/Contents/Include/tinyxml.h"
    "/Users/kristian/Dropbox/github/Polycode/Core/Contents/Include/PolySocket.h"
    "/Users/kristian/Dropbox/github/Polycode/Core/Contents/Include/PolyPeer.h"
    "/Users/kristian/Dropbox/github/Polycode/Core/Contents/Include/PolyClient.h"
    "/Users/kristian/Dropbox/github/Polycode/Core/Contents/Include/PolyServer.h"
    "/Users/kristian/Dropbox/github/Polycode/Core/Contents/Include/PolyServerWorld.h"
    "/Users/kristian/Dropbox/github/Polycode/Core/Contents/PolycodeView/Mac OS X/PolycodeView.h"
    "/Users/kristian/Dropbox/github/Polycode/Core/Contents/Include/PolyCocoaCore.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Core/PolycodeView" TYPE FILE FILES
    "/Users/kristian/Dropbox/github/Polycode/Core/Contents/PolycodeView/Mac OS X/PolycodeView.h"
    "/Users/kristian/Dropbox/github/Polycode/Core/Contents/PolycodeView/Mac OS X/PolycodeView.mm"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  FILE(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/Core/lib" TYPE STATIC_LIBRARY FILES "/Users/kristian/Dropbox/github/Polycode/Standalone/Core/Contents/libPolycore.a")
  IF(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/Core/lib/libPolycore.a" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/Core/lib/libPolycore.a")
    EXECUTE_PROCESS(COMMAND "/usr/bin/ranlib" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/Core/lib/libPolycore.a")
  ENDIF()
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

