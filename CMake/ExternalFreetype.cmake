# Build a local version
INCLUDE(ExternalProject)

SET(freetype_PREFIX ${CMAKE_CURRENT_BINARY_DIR}/freetype)

# Set the build target for the appropriate build
# TODO add other platforms
IF(MSVC10)
    SET(platform_dir "win32/vc2010")
ELSE()
    MESSAGE(ERROR "Generator support not implemented yet.")
ENDIF(MSVC10)

BUILD_COMMAND(build_TEMP 
    TARGET builds/${platform_dir}/freetype)

# split build command string into list
STRING(REPLACE " " ";" freetype_BUILD ${build_TEMP})

MESSAGE(DEBUG ${freetype_BUILD})

ExternalProject_Add(freetype
    PREFIX ${freetype_PREFIX}
    URL http://download.savannah.gnu.org/releases/freetype/freetype-2.4.5.tar.gz
    URL_MD5 0e67460b312df905dc1cc1586690e7b2
    CONFIGURE_COMMAND ${CMAKE_COMMAND} -E echo "Skipping configure step"
    BUILD_IN_SOURCE 1
    BUILD_COMMAND ${freetype_BUILD}
    INSTALL_COMMAND ${CMAKE_COMMAND} -E echo "Skipping install step"
)

# get the source dir for in source build
ExternalProject_Get_Property(freetype source_dir)

MESSAGE(DEBUG ${source_dir})

# install built files
INSTALL(DIRECTORY ${source_dir}/include 
    DESTINATION ${POLYCODE_EXTERNALS_CORE_PREFIX}
    FILES_MATCHING PATTERN "*.h")
INSTALL(DIRECTORY ${source_dir}/objs/${platform_dir}/
    DESTINATION ${POLYCODE_EXTERNALS_CORE_PREFIX}/lib/
    FILES_MATCHING PATTERN "*${CMAKE_LINK_LIBRARY_SUFFIX}")
    
#ExternalProject_Add_Step(freetype install_headers
#    COMMAND ${CMAKE_COMMAND} -E echo e1
#    DEPENDEES build
#    DEPENDERS install
#)
