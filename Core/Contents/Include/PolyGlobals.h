 
#pragma once

// TAU CORE LIBRARY CONFIGURATION SECTION

// Compile support for lua bindings.
//#define _COMPILE_LUA

#define COMPILE_GL_RENDERER

#ifdef MSVC
	#define WIN32_LEAN_AND_MEAN

	#pragma warning(disable:4251)
	#pragma warning(disable:4305)
	#pragma warning(disable:4244)
	#pragma warning(disable:4018)
	#pragma warning(disable:4996)
	#pragma warning(disable:4309)

	#define NULL 0
#endif
 
#define PI 3.14159265
#define RADIANS	57.2957795

#define TODEGREES 57.2957795
#define TORADIANS 0.0174532925

#ifdef _WINDOWS
	#define _PolyExport __declspec(dllexport)
#else
	#define _PolyExport
#endif

//#define COMPILE_SDL_CORE		1

#define PLATFORM_WINDOWS  1
#define PLATFORM_MAC      2
#define PLATFORM_UNIX     3

#ifdef _WINDOWS
	#define PLATFORM PLATFORM_WINDOWS
#elif defined(__APPLE__) && defined(__MACH__)
	#define PLATFORM PLATFORM_MAC
#else
	#define PLATFORM PLATFORM_UNIX
#endif


// NETWORK STUFF
#define MAX_PACKET_SIZE 1400

// if set to 1, will create a thread for each network socket
#define USE_THREADED_SOCKETS 0

// Socket poll interval time in msecs
#define SOCKET_POLL_INTERVAL 5



#define PACKET_TYPE_USERDATA 0
#define PACKET_TYPE_SETCLIENT_ID 1
#define PACKET_TYPE_CLIENT_READY 2
#define PACKET_TYPE_DISONNECT 3
#define PACKET_TYPE_CLIENT_DATA 4


typedef double Number;

