#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.67])

AC_INIT([libPolyCore], [0.8.2], [dev@polycode.org])
AC_CONFIG_FILES([Makefile])
AM_INIT_AUTOMAKE([libPolyCore], [0.8.2])

LT_INIT()

AC_PROG_RANLIB
AC_PROG_LIBTOOL
AC_PROG_CXX
# Checks for programs.

# Checks for libraries.

AC_CHECK_LIB([png15], [png_create_read_struct],[], [
		echo "libpng is required!"
		exit -1])

AC_CHECK_LIB([freetype], [FT_Load_Glyph],[], [
		echo "freetype is required!"
		exit -1])

AC_CHECK_LIB([vorbis], [vorbis_info_init],[], [
		echo "libvorbis is required!"
		exit -1])

AC_CHECK_LIB([vorbisfile], [ov_open_callbacks],[], [
		echo "libpng is required!"
		exit -1])

AC_CHECK_LIB([physfs], [PHYSFS_init],[], [
		echo "physfs is required!"
		exit -1])

AC_CHECK_LIB([openal], [alGenSources],[], [
		echo "openal is required!"
		exit -1])

AC_CHECK_LIB([SDL], [SDL_Init],[], [
		echo "SDL is required!"
		exit -1])

AC_CHECK_LIB([GL], [glBegin],[], [
		echo "OpenGL is required!"
		exit -1])

AC_CHECK_LIB([GLU], [gluGetString],[], [
		echo "glu is required!"
		exit -1])

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.


AC_OUTPUT
