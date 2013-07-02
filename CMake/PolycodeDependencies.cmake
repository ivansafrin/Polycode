# Find the required dependency libraries to use the polycode static library.
#
# Required variables by this cmake file:
# ${POLYCODE_CMAKE_DIR} points to the directory with all of polycode's cmake scripts(including this one)
# ${POLYCODE_RELEASE_DIR} points to the directory where the binares are produced to(Polycode/Release/${SYSTEM_NAME}) by default
#
# Sets ${POLYCODE_DEPENDENCY_LIBS} to something you can pass to TARGET_LINK_LIBRARIES
# It will use the "debug" and "optimized" cmake keywords, so it will not work for anything other than TARGET_LINK_LIBRARIES
#
#
# Uses INCLUDE_DIRECTORIES AND LINK_DIRECTORIES to add the necessary directories for the given links/includes to work.


INCLUDE(${POLYCODE_CMAKE_DIR}/PolycodeIncludes.cmake)
INCLUDE(${POLYCODE_CMAKE_DIR}/FindBullet.cmake)


INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/Include
		${POLYCODE_RELEASE_DIR}/Framework/Core/include
        ${POLYCODE_RELEASE_DIR}/Framework/Modules/include
        ${POLYCODE_RELEASE_DIR}/Framework/Core/Dependencies/include
        ${POLYCODE_RELEASE_DIR}/Framework/Core/Dependencies/include/AL
        ${PolycodeIDE_SOURCE_DIR}/include)

LINK_DIRECTORIES(${POLYCODE_RELEASE_DIR}/Framework/Core/lib
        ${POLYCODE_RELEASE_DIR}/Framework/Modules/lib
        ${POLYCODE_RELEASE_DIR}/Framework/Bindings/Lua/Core/lib
		${POLYCODE_RELEASE_DIR}/Framework/Core/Dependencies/lib)


IF(MSVC OR MINGW)
	SET(POLYCODE_DEPENDENCY_LIBS 
        PolycodeLua_d
        Polycore_d
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
        debug ${LIBBULLETMATH_DEBUG})
ELSEIF(APPLE)
	# TODO: Add apple support
ELSE(MSVC OR MINGW)
	SET(POLYCODE_DEPENDENCY_LIBS 
		rt
		pthread
		PolycodeLua_d
		PolycodeUI_d
		Polycore_d
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
		Polycode2DPhysics_d
		Polycode3DPhysics_d
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
		debug ${LIBBULLETMATH_DEBUG})
ENDIF(MSVC OR MINGW)
