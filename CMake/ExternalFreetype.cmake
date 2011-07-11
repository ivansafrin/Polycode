# Build a local version
INCLUDE(ExternalProject)

SET(freetype_PREFIX ${CMAKE_CURRENT_BINARY_DIR}/freetype)

# Set the build target for the appropriate build
# TODO add other platforms
IF(MSVC10)
    SET(platform_dir "win32/vc2010")
ELSEIF(MSVC9)
    SET(platform_dir "win32/vc2008")
ELSE()
    MESSAGE(ERROR "Generator support not implemented yet.")
ENDIF(MSVC10)

IF(DEFINED CMAKE_CFG_INTDIR)
    SET(freetype_CONFIG ${CMAKE_CFG_INTDIR})
ELSEIF(DEFINED CMAKE_BUILD_TYPE)
    SET(freetype_CONFIG ${CMAKE_CFG_INTDIR})
ENDIF()

BUILD_COMMAND(build_TEMP
    CONFIGURATION ${freetype_CONFIG}
    TARGET builds/${platform_dir}/freetype)

# split build command string into list
STRING(REPLACE " " ";" freetype_BUILD ${build_TEMP})

MESSAGE(DEBUG ${freetype_BUILD})

ExternalProject_Add(freetype
    PREFIX ${freetype_PREFIX}
    URL http://download.savannah.gnu.org/releases/freetype/freetype-2.4.5.tar.gz
    URL_MD5 0e67460b312df905dc1cc1586690e7b2
    CONFIGURE_COMMAND ""
    BUILD_IN_SOURCE 1
    BUILD_COMMAND ${freetype_BUILD}
    INSTALL_COMMAND ""
    #INSTALL_COMMAND ${CMAKE_COMMAND} -E copy_if_different <SOURCE_DIR>/objs/${platform_dir}/freetype245${CMAKE_STATIC_LIBRARY_SUFFIX} <INSTALL_DIR>/lib/freetype245${CMAKE_STATIC_LIBRARY_SUFFIX}
)

# get the source dir for in source build
ExternalProject_Get_Property(freetype source_dir)

MESSAGE(DEBUG ${source_dir})

# install built files
INSTALL(DIRECTORY ${source_dir}/include/
    DESTINATION ${POLYCODE_EXTERNALS_CORE_PREFIX}/Include
    FILES_MATCHING PATTERN "*.h")

ExternalProject_Get_Property(freetype install_dir)

# install debug lib
INSTALL(FILES ${source_dir}/objs/${platform_dir}/freetype245_D${CMAKE_STATIC_LIBRARY_SUFFIX} 
    DESTINATION ${POLYCODE_EXTERNALS_CORE_PREFIX}/Lib/Debug
    CONFIGURATIONS Debug)

# install release lib
INSTALL(FILES ${source_dir}/objs/${platform_dir}/freetype245${CMAKE_STATIC_LIBRARY_SUFFIX}
    DESTINATION ${POLYCODE_EXTERNALS_CORE_PREFIX}/Lib/Release
    CONFIGURATIONS Release)
