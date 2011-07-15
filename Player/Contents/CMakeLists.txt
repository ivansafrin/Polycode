INCLUDE(PolycodeIncludes)
    
INCLUDE_DIRECTORIES(
    ${LUA_INCLUDE_DIR}
    ${Polycode_SOURCE_DIR}/Bindings/Contents/LUA/Include
)

SET(CMAKE_DEBUG_POSTFIX "_d")

IF(MSVC)
    SET(polycodeplayer_SRCS
        ../Build/MSVC/PolycodePlayer/player_icon.ico
        ../Build/MSVC/PolycodePlayer/main.cpp
        ../Build/MSVC/PolycodePlayer/PolycodePlayerView.cpp
        Source/PolycodePlayer.cpp
        Source/PolycodeWindowsPlayer.cpp
    )
    SET(polycodeplayer_HDRS
        ../Build/MSVC/PolycodePlayer/resource.h
        ../Build/MSVC/PolycodePlayer/PolycodePlayerView.h
        Include/PolycodePlayer.h 
        Include/PolycodeWindowsPlayer.h
    )
    
    INCLUDE_DIRECTORIES(../Build/MSVC/PolycodePlayer Include)
    
    IF(POLYCODE_BUILD_SHARED)
        ADD_EXECUTABLE(PolycodePlayer WIN32 ${polycodeplayer_SRCS} ${polycodeplayer_HDRS})
        TARGET_LINK_LIBRARIES(PolycodePlayer Polycore PolycodeLua ${LUA_LIBRARY})
    ENDIF(POLYCODE_BUILD_SHARED)

    IF(POLYCODE_BUILD_STATIC)
        ADD_EXECUTABLE(PolycodePlayer_static WIN32 ${polycodeplayer_SRCS} ${polycodeplayer_HDRS})
        TARGET_LINK_LIBRARIES(PolycodePlayer_static Polycore_static PolycodeLua_static ${LUA_LIBRARY})
    ENDIF(POLYCODE_BUILD_STATIC)
    
ELSEIF(APPLE)
    SET(polycodeplayer_SRCS 
        Source/PolycodePlayer.cpp
        Source/PolycodePlayer.mm
        Source/PolycodeCocoaPlayer.mm
    )
    SET(polycodeplayer_HDRS 
        Include/PolycodePlayer.h
        Include/PolycodeCocoaPlayer.h
    )
    
    INCLUDE_DIRECTORIES(Include)
    
    IF(POLYCODE_BUILD_SHARED)
        ADD_EXECUTABLE(PolycodePlayer MACOSX_BUNDLE ${polycodeplayer_SRCS} ${polycodeplayer_HDRS})
        TARGET_LINK_LIBRARIES(PolycodePlayer Polycore PolycodeLua ${LUA_LIBRARY})
    ENDIF(POLYCODE_BUILD_SHARED)

    IF(POLYCODE_BUILD_STATIC)
        ADD_EXECUTABLE(PolycodePlayer_static MACOSX_BUNDLE ${polycodeplayer_SRCS} ${polycodeplayer_HDRS})
        TARGET_LINK_LIBRARIES(PolycodePlayer_static Polycore_static PolycodeLua ${LUA_LIBRARY})
    ENDIF(POLYCODE_BUILD_STATIC)

ENDIF(MSVC)

IF(POLYCODE_INSTALL_PLAYER)

    IF(POLYCODE_BUILD_SHARED)
        # install player
        INSTALL(TARGETS PolycodePlayer DESTINATION ${POLYCODE_RELEASE_DIR}/Player)
    ENDIF()
    IF(POLYCODE_BUILD_STATIC)
        INSTALL(TARGETS PolycodePlayer_static DESTINATION ${POLYCODE_RELEASE_DIR}/Player)
    ENDIF()
ENDIF(POLYCODE_INSTALL_PLAYER)
