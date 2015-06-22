INCLUDE(PolycodeIncludes)
    
SET(CMAKE_DEBUG_POSTFIX "_d")

IF(MSVC OR MINGW)

INCLUDE_DIRECTORIES(
    ${LUA_INCLUDE_DIR}
    ${Polycode_SOURCE_DIR}/Bindings/Contents/LUA/Include
 
    ${Polycode_SOURCE_DIR}/Modules/Contents/UI/Include
    ${Polycode_SOURCE_DIR}/Modules/Bindings/UI/Include

    ${BOX2D_INCLUDE_DIR}
    ${Polycode_SOURCE_DIR}/Modules/Contents/2DPhysics/Include
    ${Polycode_SOURCE_DIR}/Modules/Bindings/2DPhysics/Include

    ${BULLET_INCLUDE_DIR}
    ${Polycode_SOURCE_DIR}/Modules/Contents/3DPhysics/Include
    ${Polycode_SOURCE_DIR}/Modules/Bindings/3DPhysics/Include
    Include
    ../../Core/Contents/PolycodeView/MSVC/
)

SET(polycodeplayer_SRCS 
        Source/PolycodePlayer.cpp
        Source/PolycodeWindowsPlayer.cpp
        Platform/Windows/main.cpp        
    )

    SET(polycodeplayer_HDRS 
        Include/PolycodePlayer.h
        Include/PolycodeWindowsPlayer.h
        Include/resource.h
    )
  
    SET(polycodeplayerstandalone_SRCS 
        Source/PolycodePlayer.cpp
        Source/PolycodeWindowsPlayer.cpp
        Platform/Windows/Standalone/main.cpp
    )
    SET(polycodeplayerstandalone_HDRS 
        Include/PolycodePlayer.h
        Include/PolycodeWindowsPlayer.h
        Include/resource.h
    )
 
    ADD_EXECUTABLE(PolycodePlayer WIN32 Include/Polycode.rc ${polycodeplayer_SRCS} ${polycodeplayer_HDRS})
    ADD_EXECUTABLE(StandalonePlayer WIN32 Include/Polycode.rc ${polycodeplayerstandalone_SRCS} ${polycodeplayerstandalone_HDRS})
    

    TARGET_LINK_LIBRARIES(PolycodePlayer 
        PolycodeLua 
        Polycore
        ${ZLIB_LIBRARIES}
        ${LUA_LIBRARY}
        ${OPENGL_LIBRARIES}
        ${OPENAL_LIBRARY}
        ${PNG_LIBRARIES}
        ${FREETYPE_LIBRARIES}
        ${PHYSFS_LIBRARY}
        ${OGG_LIBRARY}
        ${VORBIS_LIBRARY}
        ${VORBISFILE_LIBRARY}
        opengl32
        glu32
        winmm
        ws2_32
    Physics2DLua
    Physics3DLua
    UILua
    Polycode2DPhysics
    Polycode3DPhysics
    PolycodeUI
    optimized ${BOX2D_RELEASE_LIBRARY}
    debug ${BOX2D_DEBUG_LIBRARY}
        optimized ${LIBBULLETMULTITHREADED}
        optimized ${LIBBULLETSOFTBODY} 
        optimized ${LIBBULLETDYNAMICS} 
        optimized ${LIBBULLETCOLLISION}
        optimized ${LIBBULLETMATH}            
        debug ${LIBBULLETMULTITHREADED_DEBUG}
        debug ${LIBBULLETSOFTBODY_DEBUG} 
        debug ${LIBBULLETDYNAMICS_DEBUG} 
        debug ${LIBBULLETCOLLISION_DEBUG}
        debug ${LIBBULLETMATH_DEBUG}  
     )

    TARGET_LINK_LIBRARIES(StandalonePlayer 
        PolycodeLua 
        Polycore 
        ${ZLIB_LIBRARIES}
        ${LUA_LIBRARY}
        ${OPENGL_LIBRARIES}
        ${OPENAL_LIBRARY}
        ${PNG_LIBRARIES}
        ${FREETYPE_LIBRARIES}
        ${PHYSFS_LIBRARY}
        ${OGG_LIBRARY}
        ${VORBIS_LIBRARY}
        ${VORBISFILE_LIBRARY} 
        opengl32
        glu32
        winmm
        ws2_32 
    Physics2DLua
    Physics3DLua
    UILua
    Polycode2DPhysics
    Polycode3DPhysics
    PolycodeUI
    optimized ${BOX2D_RELEASE_LIBRARY}
    debug ${BOX2D_DEBUG_LIBRARY}
        optimized ${LIBBULLETMULTITHREADED}
        optimized ${LIBBULLETSOFTBODY} 
        optimized ${LIBBULLETDYNAMICS} 
        optimized ${LIBBULLETCOLLISION}
        optimized ${LIBBULLETMATH}            
        debug ${LIBBULLETMULTITHREADED_DEBUG}
        debug ${LIBBULLETSOFTBODY_DEBUG} 
        debug ${LIBBULLETDYNAMICS_DEBUG} 
        debug ${LIBBULLETCOLLISION_DEBUG}
        debug ${LIBBULLETMATH_DEBUG} 
     )

ELSEIF(APPLE)

# Needed for LuaJIT
SET( CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} -pagezero_size 10000 -image_base 100000000" ) 
  
INCLUDE_DIRECTORIES(
    ${LUA_INCLUDE_DIR}
    ${Polycode_SOURCE_DIR}/Bindings/Contents/LUA/Include
 
    ${Polycode_SOURCE_DIR}/Modules/Contents/UI/Include
    ${Polycode_SOURCE_DIR}/Modules/Bindings/UI/Include

    ${BOX2D_INCLUDE_DIR}
    ${Polycode_SOURCE_DIR}/Modules/Contents/2DPhysics/Include
    ${Polycode_SOURCE_DIR}/Modules/Bindings/2DPhysics/Include

    ${BULLET_INCLUDE_DIR}
    ${Polycode_SOURCE_DIR}/Modules/Contents/3DPhysics/Include
    ${Polycode_SOURCE_DIR}/Modules/Bindings/3DPhysics/Include
    Include
    ../../Core/Contents/PolycodeView/Mac\ OS\ X/
)

    SET(polycodeplayer_SRCS 
        Source/PolycodePlayer.cpp
        Source/PolycodeCocoaPlayer.mm
        Platform/Darwin/main.m
        Platform/Darwin/MyDocument.mm
        Platform/Darwin/PPlayerDocumentController.mm
	../../Core/Contents/PolycodeView/Mac\ OS\ X/PolycodeView.mm
    )
    SET(polycodeplayer_HDRS 
        Include/PolycodePlayer.h
        Include/PolycodeCocoaPlayer.h
        Platform/Darwin/MyDocument.h
        Platform/Darwin/PPlayerDocumentController.h
	../../Core/Contents/PolycodeView/Mac\ OS\ X/PolycodeView.h
    )
  
    SET(polycodeplayerstandalone_SRCS 
        Source/PolycodePlayer.cpp
        Source/PolycodeCocoaPlayer.mm
        Platform/Darwin/Standalone/main.m
        Platform/Darwin/Standalone/StandalonePlayerAppDelegate.mm
	../../Core/Contents/PolycodeView/Mac\ OS\ X/PolycodeView.mm
    )
    SET(polycodeplayerstandalone_HDRS 
        Include/PolycodePlayer.h
        Include/PolycodeCocoaPlayer.h
        Platform/Darwin/Standalone/StandalonePlayerAppDelegate.h
	../../Core/Contents/PolycodeView/Mac\ OS\ X/PolycodeView.h
    )
  
    
#    IF(POLYCODE_BUILD_SHARED)
#        ADD_EXECUTABLE(PolycodePlayer MACOSX_BUNDLE ${polycodeplayer_SRCS} ${polycodeplayer_HDRS})
#        TARGET_LINK_LIBRARIES(PolycodePlayer Polycore PolycodeLua ${LUA_LIBRARY})
#    ENDIF(POLYCODE_BUILD_SHARED)

find_program(IBTOOL ibtool HINTS "/usr/bin" "${OSX_DEVELOPER_ROOT}/usr/bin")
if (${IBTOOL} STREQUAL "IBTOOL-NOTFOUND")
  message(SEND_ERROR "ibtool can not be found and is needed to compile the .xib files. It should have been installed with 
                    the Apple developer tools. The default system paths were searched in addition to ${OSX_DEVELOPER_ROOT}/usr/bin")
endif()


	set (PolycodePlayer_XIBS
		MainMenu
		MyDocument
	)

	set (PolycodePlayerStandalone_XIBS
		MainMenu
	)

    ADD_EXECUTABLE(PolycodePlayer MACOSX_BUNDLE ${polycodeplayer_SRCS} ${polycodeplayer_HDRS})
    set_target_properties( PolycodePlayer PROPERTIES MACOSX_BUNDLE_INFO_PLIST ${Polycode_SOURCE_DIR}/Player/Contents/Platform/Darwin/Info.plist )

    ADD_EXECUTABLE(StandalonePlayer MACOSX_BUNDLE ${polycodeplayerstandalone_SRCS} ${polycodeplayerstandalone_HDRS})
    set_target_properties( StandalonePlayer PROPERTIES MACOSX_BUNDLE_INFO_PLIST ${Polycode_SOURCE_DIR}/Player/Contents/Platform/Darwin/Standalone/Info.plist )

    TARGET_LINK_LIBRARIES(PolycodePlayer 
        Polycore 
        PolycodeLua 
        "-framework Cocoa"
        "-framework IOKit"
        ${LUA_LIBRARY}
        ${OPENGL_LIBRARIES}
        ${OPENAL_LIBRARY}
        ${ZLIB_LIBRARIES}
        ${PNG_LIBRARIES}
        ${FREETYPE_LIBRARIES}
        ${PHYSFS_LIBRARY}
        ${OGG_LIBRARY}
        ${VORBIS_LIBRARY}
        ${VORBISFILE_LIBRARY}
	
	${BOX2D_RELEASE_LIBRARY}
        optimized ${LIBBULLETMULTITHREADED}
        optimized ${LIBBULLETSOFTBODY} 
        optimized ${LIBBULLETDYNAMICS} 
        optimized ${LIBBULLETCOLLISION}
        optimized ${LIBBULLETMATH}            
        debug ${LIBBULLETMULTITHREADED_DEBUG}
        debug ${LIBBULLETSOFTBODY_DEBUG} 
        debug ${LIBBULLETDYNAMICS_DEBUG} 
        debug ${LIBBULLETCOLLISION_DEBUG}
        debug ${LIBBULLETMATH_DEBUG}  
	Polycode2DPhysics
	Polycode3DPhysics
	PolycodeUI
	Physics2DLua
	Physics3DLua
	UILua
	
     )

    TARGET_LINK_LIBRARIES(StandalonePlayer 
        Polycore 
        PolycodeLua 
        "-framework Cocoa"
        "-framework IOKit"
        ${LUA_LIBRARY}
        ${OPENGL_LIBRARIES}
        ${OPENAL_LIBRARY}
        ${ZLIB_LIBRARIES}
        ${PNG_LIBRARIES}
        ${FREETYPE_LIBRARIES}
        ${PHYSFS_LIBRARY}
        ${OGG_LIBRARY}
        ${VORBIS_LIBRARY}
        ${VORBISFILE_LIBRARY}
	
	${BOX2D_RELEASE_LIBRARY}
        optimized ${LIBBULLETMULTITHREADED}
        optimized ${LIBBULLETSOFTBODY} 
        optimized ${LIBBULLETDYNAMICS} 
        optimized ${LIBBULLETCOLLISION}
        optimized ${LIBBULLETMATH}            
        debug ${LIBBULLETMULTITHREADED_DEBUG}
        debug ${LIBBULLETSOFTBODY_DEBUG} 
        debug ${LIBBULLETDYNAMICS_DEBUG} 
        debug ${LIBBULLETCOLLISION_DEBUG}
        debug ${LIBBULLETMATH_DEBUG}  
	Polycode2DPhysics
	Polycode3DPhysics
	PolycodeUI
	Physics2DLua
	Physics3DLua
	UILua
     )

	add_custom_command (TARGET PolycodePlayer PRE_BUILD
                      COMMAND mkdir -p ${PROJECT_BINARY_DIR}/Player/Contents/\${CONFIGURATION}/PolycodePlayer.app/Contents/Resources)
	add_custom_command (TARGET PolycodePlayer PRE_BUILD
                      COMMAND cp ${Polycode_SOURCE_DIR}/Player/Contents/Platform/Darwin/app_file_icon.icns ${PROJECT_BINARY_DIR}/Player/Contents/\${CONFIGURATION}/PolycodePlayer.app/Contents/Resources)
	add_custom_command (TARGET PolycodePlayer PRE_BUILD
                      COMMAND cp ${Polycode_SOURCE_DIR}/Player/Contents/Platform/Darwin/player_icon.icns ${PROJECT_BINARY_DIR}/Player/Contents/\${CONFIGURATION}/PolycodePlayer.app/Contents/Resources)
	add_custom_command (TARGET PolycodePlayer PRE_BUILD
                      COMMAND cp ${Polycode_SOURCE_DIR}/Assets/Default\ asset\ pack/default.pak ${PROJECT_BINARY_DIR}/Player/Contents/\${CONFIGURATION}/PolycodePlayer.app/Contents/Resources)
    add_custom_command (TARGET PolycodePlayer PRE_BUILD
                      COMMAND cp ${Polycode_SOURCE_DIR}/Assets/Default\ asset\ pack/hdr.pak ${PROJECT_BINARY_DIR}/Player/Contents/\${CONFIGURATION}/PolycodePlayer.app/Contents/Resources)                      
	add_custom_command (TARGET PolycodePlayer PRE_BUILD
                      COMMAND cp -R ${Polycode_SOURCE_DIR}/Bindings/Contents/LUA/API/api.pak ${PROJECT_BINARY_DIR}/Player/Contents/\${CONFIGURATION}/PolycodePlayer.app/Contents/Resources)
	add_custom_command (TARGET PolycodePlayer PRE_BUILD
                      COMMAND cp -R ${Polycode_SOURCE_DIR}/Modules/Bindings/2DPhysics/API/Physics2D.pak ${PROJECT_BINARY_DIR}/Player/Contents/\${CONFIGURATION}/PolycodePlayer.app/Contents/Resources)
	add_custom_command (TARGET PolycodePlayer PRE_BUILD
                      COMMAND cp -R ${Polycode_SOURCE_DIR}/Modules/Bindings/3DPhysics/API/Physics3D.pak ${PROJECT_BINARY_DIR}/Player/Contents/\${CONFIGURATION}/PolycodePlayer.app/Contents/Resources)
	add_custom_command (TARGET PolycodePlayer PRE_BUILD
                      COMMAND cp -R ${Polycode_SOURCE_DIR}/Modules/Bindings/UI/API/UI.pak ${PROJECT_BINARY_DIR}/Player/Contents/\${CONFIGURATION}/PolycodePlayer.app/Contents/Resources)
	add_custom_command (TARGET PolycodePlayer PRE_BUILD
                      COMMAND cp -R ${Polycode_SOURCE_DIR}/Assets/UIThemes.pak ${PROJECT_BINARY_DIR}/Player/Contents/\${CONFIGURATION}/PolycodePlayer.app/Contents/Resources)

	add_custom_command (TARGET StandalonePlayer PRE_BUILD
                      COMMAND mkdir -p ${PROJECT_BINARY_DIR}/Player/Contents/\${CONFIGURATION}/StandalonePlayer.app/Contents/Resources)
	add_custom_command (TARGET StandalonePlayer PRE_BUILD
                      COMMAND cp ${Polycode_SOURCE_DIR}/Player/Contents/Platform/Darwin/player_icon.icns ${PROJECT_BINARY_DIR}/Player/Contents/\${CONFIGURATION}/StandalonePlayer.app/Contents/Resources)
	add_custom_command (TARGET StandalonePlayer PRE_BUILD
                      COMMAND cp ${Polycode_SOURCE_DIR}/Assets/Default\ asset\ pack/default.pak ${PROJECT_BINARY_DIR}/Player/Contents/\${CONFIGURATION}/StandalonePlayer.app/Contents/Resources)
    add_custom_command (TARGET StandalonePlayer PRE_BUILD
                      COMMAND cp ${Polycode_SOURCE_DIR}/Assets/Default\ asset\ pack/hdr.pak ${PROJECT_BINARY_DIR}/Player/Contents/\${CONFIGURATION}/StandalonePlayer.app/Contents/Resources)            
	add_custom_command (TARGET StandalonePlayer PRE_BUILD
                      COMMAND cp -R ${Polycode_SOURCE_DIR}/Bindings/Contents/LUA/API/api.pak ${PROJECT_BINARY_DIR}/Player/Contents/\${CONFIGURATION}/StandalonePlayer.app/Contents/Resources)
	add_custom_command (TARGET StandalonePlayer PRE_BUILD
                      COMMAND cp ${Polycode_SOURCE_DIR}/Assets/SamplePolyapp/main.polyapp ${PROJECT_BINARY_DIR}/Player/Contents/\${CONFIGURATION}/StandalonePlayer.app/Contents/Resources)
	add_custom_command (TARGET StandalonePlayer PRE_BUILD
                      COMMAND cp -R ${Polycode_SOURCE_DIR}/Modules/Bindings/2DPhysics/API/Physics2D.pak ${PROJECT_BINARY_DIR}/Player/Contents/\${CONFIGURATION}/StandalonePlayer.app/Contents/Resources)
	add_custom_command (TARGET StandalonePlayer PRE_BUILD
                      COMMAND cp -R ${Polycode_SOURCE_DIR}/Modules/Bindings/3DPhysics/API/Physics3D.pak ${PROJECT_BINARY_DIR}/Player/Contents/\${CONFIGURATION}/StandalonePlayer.app/Contents/Resources)
	add_custom_command (TARGET StandalonePlayer PRE_BUILD
                      COMMAND cp -R ${Polycode_SOURCE_DIR}/Modules/Bindings/UI/API/UI.pak ${PROJECT_BINARY_DIR}/Player/Contents/\${CONFIGURATION}/StandalonePlayer.app/Contents/Resources)
	add_custom_command (TARGET StandalonePlayer PRE_BUILD
                      COMMAND cp -R ${Polycode_SOURCE_DIR}/Assets/UIThemes.pak ${PROJECT_BINARY_DIR}/Player/Contents/\${CONFIGURATION}/PolycodePlayer.app/Contents/Resources)


foreach(xib ${PolycodePlayer_XIBS})
  add_custom_command (TARGET PolycodePlayer POST_BUILD 
                      COMMAND ${IBTOOL} --errors --warnings --notices --output-format human-readable-text 
                              --compile ${PROJECT_BINARY_DIR}/Player/Contents/\${CONFIGURATION}/PolycodePlayer.app/Contents/Resources/${xib}.nib 
                             ${Polycode_SOURCE_DIR}/Player/Contents/Platform/Darwin/${xib}.xib
                      COMMENT "Compiling ${Polycode_SOURCE_DIR}/Player/Contents/Platform/Darwin/${xib}.xib")

endforeach()


foreach(xib ${PolycodePlayerStandalone_XIBS})
  add_custom_command (TARGET StandalonePlayer POST_BUILD 
                      COMMAND ${IBTOOL} --errors --warnings --notices --output-format human-readable-text 
                              --compile ${PROJECT_BINARY_DIR}/Player/Contents/\${CONFIGURATION}/StandalonePlayer.app/Contents/Resources/${xib}.nib 
                             ${Polycode_SOURCE_DIR}/Player/Contents/Platform/Darwin/Standalone/${xib}.xib
                      COMMENT "Compiling ${Polycode_SOURCE_DIR}/Player/Contents/Platform/Darwin/Standalone/${xib}.xib")

endforeach()
ELSE(MSVC OR MINGW)

   
INCLUDE_DIRECTORIES(
    ${LUA_INCLUDE_DIR}
    ${Polycode_SOURCE_DIR}/Bindings/Contents/LUA/Include
 
    ${Polycode_SOURCE_DIR}/Modules/Contents/UI/Include
    ${Polycode_SOURCE_DIR}/Modules/Bindings/UI/Include

    ${BOX2D_INCLUDE_DIR}
    ${Polycode_SOURCE_DIR}/Modules/Contents/2DPhysics/Include
    ${Polycode_SOURCE_DIR}/Modules/Bindings/2DPhysics/Include

    ${BULLET_INCLUDE_DIR}
    ${Polycode_SOURCE_DIR}/Modules/Contents/3DPhysics/Include
    ${Polycode_SOURCE_DIR}/Modules/Bindings/3DPhysics/Include
    Include
    ../../Core/Contents/PolycodeView/Linux/
)

 SET(polycodeplayer_SRCS 
        Source/PolycodePlayer.cpp
        Source/PolycodeLinuxPlayer.cpp
        Platform/Linux/main.cpp
    )

    SET(polycodeplayer_HDRS 
        Include/PolycodePlayer.h
        Include/PolycodeLinuxPlayer.h
    )
  
    SET(polycodeplayerstandalone_SRCS 
        Source/PolycodePlayer.cpp
        Source/PolycodeLinuxPlayer.cpp
        Platform/Linux/Standalone/main.cpp
    )
    SET(polycodeplayerstandalone_HDRS 
        Include/PolycodePlayer.h
        Include/PolycodeLinuxPlayer.h
    )
 
    ADD_EXECUTABLE(PolycodePlayer ${polycodeplayer_SRCS} ${polycodeplayer_HDRS})
    ADD_EXECUTABLE(StandalonePlayer ${polycodeplayerstandalone_SRCS} ${polycodeplayerstandalone_HDRS})
    

    TARGET_LINK_LIBRARIES(PolycodePlayer 
	rt
	pthread
        PolycodeLua 
        Polycore 
        ${LUA_LIBRARY}
        ${FREETYPE_LIBRARIES}
        ${VORBISFILE_LIBRARY}
        ${VORBIS_LIBRARY}
        ${OGG_LIBRARY}
        ${OPENAL_LIBRARY}
        ${PHYSFS_LIBRARY}
        ${PNG_LIBRARIES}
        ${ZLIB_LIBRARY}
        ${OPENGL_LIBRARIES}
        ${SDL_LIBRARY}
	dl
	Physics2DLua
	Physics3DLua
	UILua
	Polycode2DPhysics
	Polycode3DPhysics
	PolycodeUI
	${BOX2D_RELEASE_LIBRARY}
        optimized ${LIBBULLETMULTITHREADED}
        optimized ${LIBBULLETSOFTBODY} 
        optimized ${LIBBULLETDYNAMICS} 
        optimized ${LIBBULLETCOLLISION}
        optimized ${LIBBULLETMATH}            
        debug ${LIBBULLETMULTITHREADED_DEBUG}
        debug ${LIBBULLETSOFTBODY_DEBUG} 
        debug ${LIBBULLETDYNAMICS_DEBUG} 
        debug ${LIBBULLETCOLLISION_DEBUG}
        debug ${LIBBULLETMATH_DEBUG}  
     )

    TARGET_LINK_LIBRARIES(StandalonePlayer 
	rt
	pthread
        PolycodeLua 
        Polycore 
        ${LUA_LIBRARY}
        ${FREETYPE_LIBRARIES}
        ${VORBISFILE_LIBRARY}
        ${VORBIS_LIBRARY}
        ${OGG_LIBRARY}
        ${OPENAL_LIBRARY}
        ${PHYSFS_LIBRARY}
        ${PNG_LIBRARIES}
        ${ZLIB_LIBRARY}
        ${OPENGL_LIBRARIES}
        ${SDL_LIBRARY}
	dl
	Physics2DLua
	Physics3DLua
	UILua
	Polycode2DPhysics
	Polycode3DPhysics
	PolycodeUI
	${BOX2D_RELEASE_LIBRARY}
        optimized ${LIBBULLETMULTITHREADED}
        optimized ${LIBBULLETSOFTBODY} 
        optimized ${LIBBULLETDYNAMICS} 
        optimized ${LIBBULLETCOLLISION}
        optimized ${LIBBULLETMATH}            
        debug ${LIBBULLETMULTITHREADED_DEBUG}
        debug ${LIBBULLETSOFTBODY_DEBUG} 
        debug ${LIBBULLETDYNAMICS_DEBUG} 
        debug ${LIBBULLETCOLLISION_DEBUG}
        debug ${LIBBULLETMATH_DEBUG}  
     )

    

ENDIF(MSVC OR MINGW)

    INSTALL(TARGETS PolycodePlayer 
        DESTINATION Player)

    INSTALL(TARGETS StandalonePlayer 
        DESTINATION Player)

IF(MSVC OR MINGW)
    INSTALL(FILES "${Polycode_SOURCE_DIR}/Assets/Default\ asset\ pack/default.pak" DESTINATION Player)
    INSTALL(FILES "${Polycode_SOURCE_DIR}/Assets/Default\ asset\ pack/hdr.pak" DESTINATION Player)
	INSTALL(FILES "${Polycode_SOURCE_DIR}/Assets/UIThemes.pak" DESTINATION Player)
    INSTALL(FILES "${Polycode_SOURCE_DIR}/Assets/SamplePolyapp/main.polyapp" DESTINATION Player)
    INSTALL(FILES "${Polycode_SOURCE_DIR}/Bindings/Contents/LUA/API/api.pak" DESTINATION Player)
    INSTALL(FILES ${POLYCODE_RELEASE_DIR}/Framework/Core/Dependencies/bin/OpenAL32.dll DESTINATION Player)
ELSEIF(APPLE)
ELSE(MSVC OR MINGW)
    INSTALL(FILES "${Polycode_SOURCE_DIR}/Assets/Default\ asset\ pack/default.pak" DESTINATION Player)
    INSTALL(FILES "${Polycode_SOURCE_DIR}/Assets/Default\ asset\ pack/hdr.pak" DESTINATION Player)
	INSTALL(FILES "${Polycode_SOURCE_DIR}/Assets/UIThemes.pak" DESTINATION Player)
    INSTALL(FILES "${Polycode_SOURCE_DIR}/Assets/SamplePolyapp/main.polyapp" DESTINATION Player)
    INSTALL(FILES "${Polycode_SOURCE_DIR}/Bindings/Contents/LUA/API/api.pak" DESTINATION Player)
ENDIF(MSVC OR MINGW)
