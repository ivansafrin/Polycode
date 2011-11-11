CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(PolycodeStandalone)

SET(POLYCODE_RELEASE_DIR ${PolycodeStandalone_SOURCE_DIR}/../Release/${CMAKE_SYSTEM_NAME})
SET(CMAKE_INSTALL_PREFIX ${POLYCODE_RELEASE_DIR}/Standalone/)

INSTALL(FILES ../LICENSE.txt
        DESTINATION ./)

INSTALL(DIRECTORY ${POLYCODE_RELEASE_DIR}/Framework/Player/PolycodePlayer.app DESTINATION Player USE_SOURCE_PERMISSIONS)
INSTALL(DIRECTORY ${POLYCODE_RELEASE_DIR}/Framework/Player/StandalonePlayer.app DESTINATION Publish/Mac USE_SOURCE_PERMISSIONS)
INSTALL(PROGRAMS ${POLYCODE_RELEASE_DIR}/Framework/Tools/polybuild DESTINATION Bin)
INSTALL(PROGRAMS ${POLYCODE_RELEASE_DIR}/Framework/Tools/polyimport DESTINATION Bin)
INSTALL(DIRECTORY ${PolycodeStandalone_SOURCE_DIR}/../Assets/Templates/Lua DESTINATION Template)

#modules
INSTALL(DIRECTORY ${PolycodeStandalone_SOURCE_DIR}/../Modules/Bindings/2DPhysics/API DESTINATION Modules/Physics2D)
INSTALL(FILES ${POLYCODE_RELEASE_DIR}/Framework/Bindings/Lua/Modules/2DPhysics/lib/Physics2D.dylib DESTINATION Modules/Physics2D/Lib/osx)

INSTALL(DIRECTORY ${PolycodeStandalone_SOURCE_DIR}/../Modules/Bindings/3DPhysics/API DESTINATION Modules/Physics3D)
INSTALL(FILES ${POLYCODE_RELEASE_DIR}/Framework/Bindings/Lua/Modules/3DPhysics/lib/Physics3D.dylib DESTINATION Modules/Physics3D/Lib/osx)

