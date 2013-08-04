# the name of the target operating system
SET(CMAKE_SYSTEM_NAME Windows)

# which compilers to use for C and C++
SET(CMAKE_C_COMPILER i486-mingw32-gcc)
SET(CMAKE_CXX_COMPILER i486-mingw32-g++)
SET(CMAKE_RC_COMPILER i486-mingw32-windres)

# here is the target environment located, please replace /path/to/Polycode with the absolute path to your polycode installation
SET(POLYCODE_DIRECTORY "/path/to/Polycode")
SET(CMAKE_FIND_ROOT_PATH  /usr/i486-mingw32; ${POLYCODE_DIRECTORY}/Release/Windows/Framework/Core/Dependencies; ${POLYCODE_DIRECTORY}/Release/Windows/Framework/Tools/Dependencies; /home/cib/projects/Polycode/Release/Windows/Framework/Modules/Dependencies; )

# adjust the default behaviour of the FIND_XXX() commands:
# search headers and libraries in the target environment, search 
# programs in the host environment
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

# Paste the below into the relevant cmake files.
#set(CMAKE_CXX_FLAGS "-D_WINDOWS -D_MINGW -D_WIN32 -DWIN32 -D__MINGW__")
