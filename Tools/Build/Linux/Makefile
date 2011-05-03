INC_POLYIMPORT= -I../../../Core/Dependencies/physfs/ -I../../Contents/polyimport/Include -I../../Dependencies/assimp/include/ -I../../../Core/Contents/Include/
LIB_POLYIMPORT= ../../Dependencies/assimp/lib/libassimp.dylib ../../../Core/Dependencies/physfs/Debug/libphysfs.a ../../../Release/Mac\ OS\ X/Framework/Core/Lib/libPolyCore.a -framework IOKit -framework Cocoa
polyimport:
	g++ -g ../../Contents/polyimport/Source/*.cpp $(INC_POLYIMPORT) $(LIB_POLYIMPORT) -o polyimport

LIB_POLYBUILD=  ../../../Core/Dependencies/physfs/Debug/libphysfs.a ../../../Release/Mac\ OS\ X/Framework/Core/Lib/libPolyCore.a -framework IOKit -framework Cocoa 
INC_POLYBUILD= -I../../../Core/Dependencies/physfs/ -I../../../Core/Dependencies/zlib/ -I../../Contents/polybuild/Include -I../../../Core/Contents/Include/ -I../../Dependencies/unzip11/ 
polybuild:
	g++ -g ../../../Core/Dependencies/zlib/libz.a ../../Contents/polybuild/Source/*.cpp ../../Dependencies/unzip11/ioapi.c ../../Dependencies/unzip11/zip.c $(INC_POLYBUILD) $(LIB_POLYBUILD) -o polybuild
