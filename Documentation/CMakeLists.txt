IF(POLYCODE_BUILD_DOCS)

FIND_PACKAGE(Doxygen)

IF(DOXYGEN_FOUND)

FILE(GLOB HEADER_DEPENDENCIES_CORE ${Polycode_SOURCE_DIR}/Core/Contents/Include/*.h)
FILE(GLOB HEADER_DEPENDENCIES_2DPHYSICS ${Polycode_SOURCE_DIR}/Modules/Contents/2DPhysics/Include/*.h)
FILE(GLOB HEADER_DEPENDENCIES_3DPHYSICS ${Polycode_SOURCE_DIR}/Modules/Contents/3DPhysics/Include/*.h)
FILE(GLOB HEADER_DEPENDENCIES_UI ${Polycode_SOURCE_DIR}/Modules/Contents/UI/Include/*.h)

ADD_CUSTOM_COMMAND(
OUTPUT doc_cmd
COMMAND ${DOXYGEN_EXECUTABLE} ${Polycode_SOURCE_DIR}/Documentation/Doxygen/Polycode.doxygen
COMMAND ${DOXYGEN_EXECUTABLE} ${Polycode_SOURCE_DIR}/Documentation/Doxygen/Physics2D.doxygen
COMMAND ${DOXYGEN_EXECUTABLE} ${Polycode_SOURCE_DIR}/Documentation/Doxygen/Physics3D.doxygen
COMMAND ${DOXYGEN_EXECUTABLE} ${Polycode_SOURCE_DIR}/Documentation/Doxygen/Polycode_ui.doxygen
COMMAND ${CMAKE_COMMAND} -E touch ${CMAKE_CURRENT_BINARY_DIR}/doc_cmd # Generate the given output file(empty file), to keep track of whether we need to rebuild.
WORKING_DIRECTORY ${Polycode_SOURCE_DIR}/Documentation/Doxygen/
DEPENDS ${HEADER_DEPENDENCIES_CORE} ${HEADER_DEPENDENCIES_2DPHYSICS} ${HEADER_DEPENDENCIES_3DPHYSICS} ${HEADER_DEPENDENCIES_UI}
COMMENT "Generating Polycode API documentation with Doxygen" VERBATIM
)

ADD_CUSTOM_TARGET(doc ALL DEPENDS doc_cmd)

INSTALL(DIRECTORY Doxygen/output/standalone/Core
        DESTINATION Docs)
INSTALL(DIRECTORY Doxygen/output/standalone/Physics2D
        DESTINATION Docs/Modules)
INSTALL(DIRECTORY Doxygen/output/standalone/Physics3D
        DESTINATION Docs/Modules)
INSTALL(DIRECTORY Doxygen/output/standalone/PolycodeUI
		DESTINATION Docs/Modules)
		
ENDIF(DOXYGEN_FOUND)

ENDIF(POLYCODE_BUILD_DOCS)
