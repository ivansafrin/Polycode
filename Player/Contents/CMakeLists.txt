INCLUDE_DIRECTORIES(
    ${LUA_INCLUDE_DIR}
    ${PolyCode_SOURCE_DIR}/Bindings/Contents/LUA/Include
)

IF(MSVC)
    SET(polycodeplayer_SRCS
        ../Build/MSVC/PolycodePlayer/main.cpp
        ../Build/MSVC/PolycodePlayer/PolycodePlayerView.cpp
        Source/PolycodePlayer.cpp
        Source/PolycodeWindowsPlayer.cpp
    )
    SET(polycodeplayer_HDRS 
        ../Build/MSVC/PolycodePlayer/PolycodePlayerView.h
        Include/PolycodePlayer.h 
        Include/PolycodeWindowsPlayer.h
    )
    
    INCLUDE_DIRECTORIES(../Build/MSVC/PolycodePlayer Include)
    
    IF(POLYCODE_BUILD_SHARED)
        ADD_EXECUTABLE(PolycodePlayer WIN32 ${polycodeplayer_SRCS} ${polycodeplayer_HDRS})
        TARGET_LINK_LIBRARIES(PolycodePlayer PolyCore PolycodeLua ${LUA_LIBRARY})
    ENDIF(POLYCODE_BUILD_SHARED)

    IF(POLYCODE_BUILD_STATIC)
        ADD_EXECUTABLE(PolycodePlayer_static WIN32 ${polycodeplayer_SRCS} ${polycodeplayer_HDRS})
        TARGET_LINK_LIBRARIES(PolycodePlayer_static PolyCore_static PolycodeLua_static ${LUA_LIBRARY})
    ENDIF(POLYCODE_BUILD_STATIC)
    
ELSEIF(APPLE)
    SET(polycodeplayer_SRCS 
        Source/PolycodePlayer.cpp
        Source/PolycodePlayer.mm
        Source/PolycodeCocoaPlayer.mm
    )
    SEY(polycodeplayer_HDRS 
        Include/PolycodePlayer.h
        Include/PolycodeCocoaPlayer.h
    )
    
    INCLUDE_DIRECTORIES(Include)
    
    IF(POLYCODE_BUILD_SHARED)
        ADD_EXECUTABLE(PolycodePlayer MACOSX_BUNDLE ${polycodeplayer_SRCS} ${polycodeplayer_HDRS})
        TARGET_LINK_LIBRARIES(PolycodePlayer PolyCore PolycodeLua ${LUA_LIBRARY})
    ENDIF(POLYCODE_BUILD_SHARED)

    IF(POLYCODE_BUILD_STATIC)
        ADD_EXECUTABLE(PolycodePlayer_static MACOSX_BUNDLE ${polycodeplayer_SRCS} ${polycodeplayer_HDRS})
        TARGET_LINK_LIBRARIES(PolycodePlayer_static PolyCore_static PolycodeLua_static ${LUA_LIBRARY})
    ENDIF(POLYCODE_BUILD_STATIC)

ENDIF(MSVC)

