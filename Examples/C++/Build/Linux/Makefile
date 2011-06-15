CC=g++
CFLAGS=-I../../Core/Dependencies/include -I../../Core/Dependencies/include/AL -I../../Core/include
LDFLAGS=../../Core/lib/libPolycore.a ../../Core/Dependencies/lib/libfreetype.a ../../Core/Dependencies/lib/liblibogg.a ../../Core/Dependencies/lib/liblibvorbis.a ../../Core/Dependencies/lib/liblibvorbisfile.a ../../Core/Dependencies/lib/libopenal.a ../../Core/Dependencies/lib/libphysfs.a ../../Core/Dependencies/lib/libpng15.a ../../Core/Dependencies/lib/libz.a -lGL -lGLU -lSDL

default: BasicText BasicImage

clean:
	rm BasicText
	rm BasicImage

BasicText:
	${CC} $(CFLAGS) -I./Contents/BasicText main.cpp Contents/BasicText/HelloPolycodeApp.cpp -o BasicText $(LDFLAGS)
BasicImage:
	${CC} $(CFLAGS) -I./Contents/BasicImage main.cpp Contents/BasicImage/HelloPolycodeApp.cpp -o BasicImage $(LDFLAGS)
