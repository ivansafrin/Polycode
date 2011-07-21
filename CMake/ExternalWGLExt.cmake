# download some headers missing from Windows
IF(NOT EXISTS ${POLYCODE_DEPS_DOWNLOAD_DIR}/wglext.h)
    MESSAGE("Downloading http://www.opengl.org/registry/api/wglext.h")
    FILE(DOWNLOAD http://www.opengl.org/registry/api/wglext.h 
        ${POLYCODE_DEPS_DOWNLOAD_DIR}/wglext.h
        SHOW_PROGRESS)
ENDIF()

ADD_CUSTOM_TARGET(wglext
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${POLYCODE_DEPS_DOWNLOAD_DIR}/wglext.h ${POLYCODE_DEPS_CORE_PREFIX}/include/GL/wglext.h)
