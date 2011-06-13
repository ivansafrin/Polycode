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

AC_CHECK_LIB([PolyCore], [png_create_read_struct],[], [
		echo "libpng is required!"
		exit -1])

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.


AC_OUTPUT
