# download some headers missing from Windows

IF(NOT EXISTS ${POLYCODE_DEPS_DOWNLOAD_DIR}/glext.h)
    MESSAGE("Downloading http://www.opengl.org/registry/api/glext.h")
    FILE(DOWNLOAD http://www.opengl.org/registry/api/glext.h 
        ${POLYCODE_DEPS_DOWNLOAD_DIR}/glext.h
        SHOW_PROGRESS)
ENDIF()

IF(NOT EXISTS ${POLYCODE_DEPS_DOWNLOAD_DIR}/wglext.h)
    MESSAGE("Downloading http://www.opengl.org/registry/api/wglext.h")
    FILE(DOWNLOAD http://www.opengl.org/registry/api/wglext.h 
        ${POLYCODE_DEPS_DOWNLOAD_DIR}/wglext.h
        SHOW_PROGRESS)
ENDIF()

ADD_CUSTOM_TARGET(glext
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${POLYCODE_DEPS_DOWNLOAD_DIR}/glext.h ${POLYCODE_DEPS_CORE_PREFIX}/include/GL/glext.h
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${POLYCODE_DEPS_DOWNLOAD_DIR}/wglext.h ${POLYCODE_DEPS_CORE_PREFIX}/include/GL/wglext.h)
