# download some headers missing from Windows
SET(GLEXT_H ${POLYCODE_DEPS_CORE_PREFIX}/Include/GL/glext.h)
IF(NOT EXISTS ${GLEXT_H})
    FILE(DOWNLOAD http://www.opengl.org/registry/api/glext.h 
        ${GLEXT_H}
        SHOW_PROGRESS)
ENDIF(NOT EXISTS ${GLEXT_H})

SET(WGLEXT_H ${POLYCODE_DEPS_CORE_PREFIX}/Include/GL/wglext.h)
IF(NOT EXISTS ${WGLEXT_H})
    FILE(DOWNLOAD http://www.opengl.org/registry/api/wglext.h 
        ${WGLEXT_H}
        SHOW_PROGRESS)
ENDIF(NOT EXISTS ${WGLEXT_H})
