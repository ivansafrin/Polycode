CC=g++
CFLAGS=-I../../../Release/Linux/Framework/Core/Dependencies/include -I../../../Release/Linux/Framework/Core/Dependencies/include/freetype2 -I../../../Release/Linux/Framework/Core/Dependencies/include/AL -I../../../Release/Linux/Framework/Core/include -I../../../Release/Linux/Framework/Modules/include -I../../../Release/Linux/Framework/Modules/Dependencies/include -I../../../Release/Linux/Framework/Modules/Dependencies/include/bullet -I../../Contents/Include -I../../../Release/Linux/Framework/Bindings/Lua/Core/include -I../../../Release/Linux/Framework/Core/Dependencies/include/lua5.1
LDFLAGS=../../../Release/Linux/Framework/Core/lib/libPolycore.a ../../../Release/Linux/Framework/Core/Dependencies/lib/libfreetype.a ../../../Release/Linux/Framework/Core/Dependencies/lib/liblibvorbisfile.a ../../../Release/Linux/Framework/Core/Dependencies/lib/liblibvorbis.a ../../../Release/Linux/Framework/Core/Dependencies/lib/liblibogg.a ../../../Release/Linux/Framework/Core/Dependencies/lib/libopenal.a ../../../Release/Linux/Framework/Core/Dependencies/lib/libphysfs.a ../../../Release/Linux/Framework/Core/Dependencies/lib/libpng15.a ../../../Release/Linux/Framework/Core/Dependencies/lib/libz.a -lGL -lGLU -lSDL ../../../Release/Linux/Framework/Core/Dependencies/lib/liblua5.1.a ../../../Release/Linux/Framework/Bindings/Lua/Core/lib/libPolycodeLua.a

default:
	$(CC) $(CFLAGS) main.cpp ../../Contents/Source/PolycodePlayer.cpp ../../Contents/Source/PolycodeLinuxPlayer.cpp -o PolycodePlayer $(LDFLAGS)
	cp ../../../Release/Linux/Framework/Core/Assets/default.pak .
clean:
	rm PolycodePlayer
	rm default.pak
	
