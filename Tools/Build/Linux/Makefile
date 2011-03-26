INC= -I../../../Core/Dependencies/physfs/ -I../../Contents/polyimport/Include -I../../Dependencies/assimp/include/ -I../../../Core/Contents/Include/
LIB= ../../Dependencies/assimp/lib/libassimp.dylib ../../../Core/Dependencies/physfs/Debug/libphysfs.a ../../../Core/Build/Mac\ OS\ X/build/Debug/libPolyCore.a -framework IOKit -framework Cocoa
default:
	g++ -g ../../Contents/polyimport/Source/*.cpp $(INC) $(LIB) -o polyimport
