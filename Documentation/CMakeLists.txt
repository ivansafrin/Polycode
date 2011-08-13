IF(POLYCODE_BUILD_DOCS)

FIND_PACKAGE(Doxygen)

IF(DOXYGEN_FOUND)

ADD_CUSTOM_COMMAND(
OUTPUT doc_cmd
COMMAND ${DOXYGEN_EXECUTABLE} ${Polycode_SOURCE_DIR}/Documentation/Doxygen/Polycode.doxygen
COMMAND ${DOXYGEN_EXECUTABLE} ${Polycode_SOURCE_DIR}/Documentation/Doxygen/Physics2D.doxygen
COMMAND ${DOXYGEN_EXECUTABLE} ${Polycode_SOURCE_DIR}/Documentation/Doxygen/Physics3D.doxygen
WORKING_DIRECTORY ${Polycode_SOURCE_DIR}/Documentation/Doxygen/
COMMENT "Generating Polycode API documentation with Doxygen" VERBATIM
)

ADD_CUSTOM_TARGET(doc ALL DEPENDS doc_cmd)

INSTALL(DIRECTORY Doxygen/output/standalone/Polycode
        DESTINATION Docs)
INSTALL(DIRECTORY Doxygen/output/standalone/Physics2D
        DESTINATION Docs/Modules)
INSTALL(DIRECTORY Doxygen/output/standalone/Physics3D
        DESTINATION Docs/Modules)

ENDIF(DOXYGEN_FOUND)

ENDIF(POLYCODE_BUILD_DOCS)
