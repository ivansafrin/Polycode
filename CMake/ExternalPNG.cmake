# Build a local version of zlib and libpng
INCLUDE(ExternalProject)

SET(png_PREFIX ${CMAKE_CURRENT_BINARY_DIR}/png)

EXTERNALPROJECT_ADD(zlib
    PREFIX ${png_PREFIX}

    DOWNLOAD_DIR ${POLYCODE_DEPS_DOWNLOAD_DIR}
    URL http://zlib.net/zlib-1.2.5.tar.gz
    URL_MD5 c735eab2d659a96e5a594c9e8541ad63

    PATCH_COMMAND ${CMAKE_COMMAND} -E remove <SOURCE_DIR>/zconf.h

    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
)

ExternalProject_Get_Property(zlib install_dir)

EXTERNALPROJECT_ADD(libpng
    DEPENDS zlib
    PREFIX ${png_PREFIX}

    DOWNLOAD_DIR ${POLYCODE_DEPS_DOWNLOAD_DIR}
    URL ftp://ftp.simplesystems.org/pub/libpng/png/src/libpng-1.5.4.tar.gz
    URL_MD5 dea4d1fd671160424923e92ff0cdda78

    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR> -DCMAKE_PREFIX_PATH=${install_dir} # to find zlib
)

ExternalProject_Get_Property(libpng install_dir)

# install built files
INSTALL(DIRECTORY ${install_dir}/include/
    DESTINATION ${POLYCODE_DEPS_CORE_PREFIX}/Include
    FILES_MATCHING PATTERN "*.h")

# install debug libs
INSTALL(FILES ${install_dir}/lib/zlibd${CMAKE_STATIC_LIBRARY_SUFFIX} 
    DESTINATION ${POLYCODE_DEPS_CORE_PREFIX}/Lib
    CONFIGURATIONS Debug)

INSTALL(FILES ${install_dir}/lib/libpng15d${CMAKE_STATIC_LIBRARY_SUFFIX} 
    DESTINATION ${POLYCODE_DEPS_CORE_PREFIX}/Lib
    CONFIGURATIONS Debug)

# install release lib
INSTALL(FILES ${install_dir}/lib/zlib${CMAKE_STATIC_LIBRARY_SUFFIX}
    DESTINATION ${POLYCODE_DEPS_CORE_PREFIX}/Lib
    CONFIGURATIONS Release)

INSTALL(FILES ${install_dir}/lib/libpng15${CMAKE_STATIC_LIBRARY_SUFFIX}
    DESTINATION ${POLYCODE_DEPS_CORE_PREFIX}/Lib
    CONFIGURATIONS Release)

# install debug shared library
INSTALL(FILES ${install_dir}/bin/zlibd1${CMAKE_SHARED_LIBRARY_SUFFIX}
    DESTINATION ${POLYCODE_DEPS_CORE_PREFIX}/Bin
    CONFIGURATIONS Debug)

INSTALL(FILES ${install_dir}/bin/libpng15d${CMAKE_SHARED_LIBRARY_SUFFIX}
    DESTINATION ${POLYCODE_DEPS_CORE_PREFIX}/Bin
    CONFIGURATIONS Debug)

# install release shared library
INSTALL(FILES ${install_dir}/bin/zlib1${CMAKE_SHARED_LIBRARY_SUFFIX} 
    DESTINATION ${POLYCODE_DEPS_CORE_PREFIX}/Bin
    CONFIGURATIONS Release)

INSTALL(FILES ${install_dir}/bin/libpng15${CMAKE_SHARED_LIBRARY_SUFFIX} 
    DESTINATION ${POLYCODE_DEPS_CORE_PREFIX}/Bin
    CONFIGURATIONS Release)
