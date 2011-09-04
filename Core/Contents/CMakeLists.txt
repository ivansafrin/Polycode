# set up common includes
INCLUDE(PolycodeIncludes)

SET(polycore_SRCS
    Source/OSBasics.cpp
    Source/PolyBezierCurve.cpp
    Source/PolyBone.cpp
    Source/PolyCamera.cpp
    Source/PolyColor.cpp
    Source/PolyConfig.cpp
    Source/PolyCore.cpp
    Source/PolyCoreInput.cpp
    Source/PolyCoreServices.cpp
    Source/PolyCubemap.cpp
    Source/PolyData.cpp
    Source/PolyEntity.cpp
    Source/PolyEvent.cpp
    Source/PolyEventDispatcher.cpp
    Source/PolyEventHandler.cpp
    Source/PolyFixedShader.cpp
    Source/PolyFont.cpp
    Source/PolyFontManager.cpp
    Source/PolyGLCubemap.cpp
    Source/PolyGLRenderer.cpp
    Source/PolyGLSLProgram.cpp
    Source/PolyGLSLShader.cpp
    Source/PolyGLSLShaderModule.cpp
    Source/PolyGLTexture.cpp
    Source/PolyGLVertexBuffer.cpp
    Source/PolyImage.cpp
    Source/PolyInputEvent.cpp
    Source/PolyLabel.cpp
    Source/PolyLogger.cpp
    Source/PolyMaterial.cpp
    Source/PolyMaterialManager.cpp
    Source/PolyMatrix4.cpp
    Source/PolyMesh.cpp
    Source/PolyModule.cpp
    Source/PolyObject.cpp
    Source/PolyParticle.cpp
    Source/PolyParticleEmitter.cpp
    Source/PolyPerlin.cpp
    Source/PolyPolygon.cpp
    Source/PolyQuaternion.cpp
    Source/PolyQuaternionCurve.cpp
    Source/PolyRectangle.cpp
    Source/PolyRenderer.cpp
    Source/PolyResource.cpp
    Source/PolyResourceManager.cpp
    Source/PolyScene.cpp
    Source/PolySceneEntity.cpp
    Source/PolySceneLabel.cpp
    Source/PolySceneLight.cpp
    Source/PolySceneLine.cpp
    Source/PolySceneManager.cpp
    Source/PolySceneMesh.cpp
    Source/PolyScenePrimitive.cpp
    Source/PolySceneRenderTexture.cpp
    Source/PolySceneSound.cpp
    Source/PolyScreen.cpp
    Source/PolyScreenCurve.cpp
    Source/PolyScreenEntity.cpp
    Source/PolyScreenEvent.cpp
    Source/PolyScreenImage.cpp
    Source/PolyScreenLabel.cpp
    Source/PolyScreenLine.cpp
    Source/PolyScreenManager.cpp
    Source/PolyScreenMesh.cpp
    Source/PolyScreenShape.cpp
    Source/PolyScreenSound.cpp
    Source/PolyScreenSprite.cpp
    Source/PolyShader.cpp
    Source/PolySkeleton.cpp
    Source/PolySound.cpp
    Source/PolySoundManager.cpp
    Source/PolyString.cpp
    Source/PolyTexture.cpp
    Source/PolyTimer.cpp
    Source/PolyTimerManager.cpp
    Source/PolyTween.cpp
    Source/PolyTweenManager.cpp
    Source/PolyVector2.cpp
    Source/PolyVector3.cpp
    Source/PolyVertex.cpp
    Source/tinystr.cpp
    Source/tinyxml.cpp
    Source/tinyxmlerror.cpp
    Source/tinyxmlparser.cpp
)

SET(polycore_HDRS
    Include/OSBasics.h
    Include/PolyBasics.h
    Include/PolyBezierCurve.h
    Include/PolyBone.h
    Include/PolyCamera.h
    Include/Polycode.h
    Include/PolyColor.h
    Include/PolyConfig.h
    Include/PolyCore.h
    Include/PolyCoreInput.h
    Include/PolyCoreServices.h
    Include/PolyCubemap.h
    Include/PolyData.h
    Include/PolyEntity.h
    Include/PolyEventDispatcher.h
    Include/PolyEvent.h
    Include/PolyEventHandler.h
    Include/PolyFixedShader.h
    Include/PolyFont.h
    Include/PolyFontManager.h
    Include/PolyGLCubemap.h
    Include/PolyGlobals.h
    Include/PolyGLRenderer.h
    Include/PolyGLSLProgram.h
    Include/PolyGLSLShader.h
    Include/PolyGLSLShaderModule.h
    Include/PolyGLTexture.h
    Include/PolyGLVertexBuffer.h
    Include/PolyImage.h
    Include/PolyInputEvent.h
    Include/PolyInputKeys.h
    Include/PolyLabel.h
    Include/PolyLogger.h
    Include/PolyMaterial.h
    Include/PolyMaterialManager.h
    Include/PolyMatrix4.h
    Include/PolyMesh.h
    Include/PolyModule.h
    Include/PolyObject.h
    Include/PolyParticleEmitter.h
    Include/PolyParticle.h
    Include/PolyPerlin.h
    Include/PolyPolygon.h
    Include/PolyQuaternionCurve.h
    Include/PolyQuaternion.h
    Include/PolyRectangle.h
    Include/PolyRenderer.h
    Include/PolyResource.h
    Include/PolyResourceManager.h
    Include/PolySceneEntity.h
    Include/PolyScene.h
    Include/PolySceneLabel.h
    Include/PolySceneLight.h
    Include/PolySceneLine.h
    Include/PolySceneManager.h
    Include/PolySceneMesh.h
    Include/PolyScenePrimitive.h
    Include/PolySceneRenderTexture.h
    Include/PolySceneSound.h
    Include/PolyScreenCurve.h
    Include/PolyScreenEntity.h
    Include/PolyScreenEvent.h
    Include/PolyScreen.h
    Include/PolyScreenImage.h
    Include/PolyScreenLabel.h
    Include/PolyScreenLine.h
    Include/PolyScreenManager.h
    Include/PolyScreenMesh.h
    Include/PolyScreenShape.h
    Include/PolyScreenSound.h
    Include/PolyScreenSprite.h
    Include/PolyShader.h
    Include/PolySkeleton.h
    Include/PolySound.h
    Include/PolySoundManager.h
    Include/PolyString.h
    Include/PolyTexture.h
    Include/PolyThreaded.h
    Include/PolyTimer.h
    Include/PolyTimerManager.h
    Include/PolyTween.h
    Include/PolyTweenManager.h
    Include/PolyVector2.h
    Include/PolyVector3.h
    Include/PolyVertex.h
    Include/tinystr.h
    Include/tinyxml.h
)

SET(CMAKE_DEBUG_POSTFIX "_d")

# TODO: iPhone
#    Include/PolyiPhoneCore.h
#    Include/Poly_iPhone.h
#    Source/PolyiPhoneCore.cpp

# TODO: PolyGLES1
#   Include/PolyGLES1Renderer.h
#   Include/PolyGLES1Texture.h
#   Source/PolyGLES1Renderer.cpp
#   Source/PolyGLES1Texture.cpp

# platform specific
IF(MSVC)
    SET(polycore_SRCS ${polycore_SRCS} PolycodeView/MSVC/PolycodeView.cpp Source/PolyWinCore.cpp)
    SET(polycore_HDRS ${polycore_HDRS} PolycodeView/MSVC/PolycodeView.h Include/PolyWinCore.h)
ELSEIF(APPLE)
    SET(polycore_SRCS ${polycore_SRCS} "PolycodeView/Mac OS X/PolycodeView.mm" Source/PolyCocoaCore.mm)
    SET(polycore_HDRS ${polycore_HDRS} "PolycodeView/Mac OS X/PolycodeView.h" Include/PolyCocoaCore.h)
#    SET(EXTRA_LIBS "-framework Cocoa")
ELSE(MSVC)
    SET(polycore_SRCS ${polycore_SRCS} PolycodeView/Linux/PolycodeView.cpp Source/PolySDLCore.cpp)
    SET(polycore_HDRS ${polycore_HDRS} PolycodeView/Linux/PolycodeView.h Include/PolySDLCore.h)
ENDIF(MSVC)

#IF(POLYCODE_BUILD_SHARED)
#    ADD_LIBRARY(Polycore_dynamic SHARED ${polycore_SRCS} ${polycore_HDRS})
#    TARGET_LINK_LIBRARIES(Polycore_dynamic
#        ${OPENGL_LIBRARIES}
#        ${OPENAL_LIBRARY}
#        ${PNG_LIBRARIES}
#        ${FREETYPE_LIBRARIES}
#        ${PHYSFS_LIBRARY}
#        ${OGG_LIBRARIES}
#        ${VORBIS_LIBRARIES}
#        ${VORBISFILE_LIBRARIES}
#        ${SDL_LIBRARY}
#        ${EXTRA_LIBS})
#ENDIF(POLYCODE_BUILD_SHARED)

#IF(POLYCODE_BUILD_STATIC)
ADD_LIBRARY(Polycore ${polycore_SRCS} ${polycore_HDRS})
#ENDIF(POLYCODE_BUILD_STATIC)

IF(POLYCODE_INSTALL_FRAMEWORK)
    # install headers
    INSTALL(FILES ${polycore_HDRS} 
        DESTINATION Core/include)


	IF(APPLE)
	    INSTALL(FILES "PolycodeView/Mac OS X/PolycodeView.h" "PolycodeView/Mac OS X/PolycodeView.mm"
		DESTINATION "Core/PolycodeView")
	ENDIF(APPLE)

    # install libraries
#   IF(POLYCODE_BUILD_SHARED)
#       INSTALL(TARGETS Polycore_dynamic EXPORT Polycore-targets
#           DESTINATION ${POLYCODE_RELEASE_DIR}/Framework/Core/lib)
#   ENDIF(POLYCODE_BUILD_SHARED)
    
#    IF(POLYCODE_BUILD_STATIC)
        INSTALL(TARGETS Polycore EXPORT Polycore-targets 
            DESTINATION Core/lib)
#    ENDIF(POLYCODE_BUILD_STATIC)
ENDIF(POLYCODE_INSTALL_FRAMEWORK)

IF(POLYCODE_INSTALL_PLAYER)
    # install core libs for player
#    IF(POLYCODE_BUILD_SHARED)
#        INSTALL(TARGETS Polycore_dynamic DESTINATION ${POLYCODE_RELEASE_DIR}/Player)
#    END(POLYCODE_BUILD_SHARED)
    
#    INSTALL(DIRECTORY ${POLYCODE_RELEASE_DIR}/Framework/Core/Dependencies/bin/ 
 #       DESTINATION ${POLYCODE_RELEASE_DIR}/Player)
ENDIF(POLYCODE_INSTALL_PLAYER)
