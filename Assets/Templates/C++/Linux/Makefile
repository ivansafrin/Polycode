CC=g++
CFLAGS=-I../../Core/Dependencies/include -I../../Core/Dependencies/include/AL -I../../Core/Dependencies/include/freetype2 -I../../Core/include -I../../Modules/include -I../../Modules/Dependencies/include -I../../Modules/Dependencies/include/bullet
LDFLAGS=-lrt -ldl -lpthread ../../Core/lib/libPolycore.a ../../Core/Dependencies/lib/libfreetype.a ../../Core/Dependencies/lib/liblibvorbisfile.a ../../Core/Dependencies/lib/liblibvorbis.a ../../Core/Dependencies/lib/liblibogg.a ../../Core/Dependencies/lib/libopenal.so ../../Core/Dependencies/lib/libphysfs.a ../../Core/Dependencies/lib/libpng15.a ../../Core/Dependencies/lib/libz.a -lGL -lGLU -lSDL ../../Modules/lib/libPolycode2DPhysics.a ../../Modules/Dependencies/lib/libBox2D.a ../../Modules/lib/libPolycode3DPhysics.a ../../Modules/Dependencies/lib/libBulletDynamics.a ../../Modules/Dependencies/lib/libBulletCollision.a ../../Modules/Dependencies/lib/libLinearMath.a -lX11

default:
	$(CC) $(CFLAGS) main.cpp HelloPolycodeApp.cpp -o PolycodeTemplate $(LDFLAGS)
	cp ../../Core/Assets/default.pak .
clean:
	rm PolycodeTemplate
	rm default.pak
	
