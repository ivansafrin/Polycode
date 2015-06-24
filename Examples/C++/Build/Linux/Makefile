CC=g++
CFLAGS=-I../../Core/Dependencies/include -I../../Core/Dependencies/include/AL -I../../Core/Dependencies/include/freetype2 -I../../Core/include -I../../Modules/include -I../../Modules/Dependencies/include -I../../Modules/Dependencies/include/bullet
LDFLAGS=-lrt -ldl -lpthread ../../Core/lib/libPolycore.a ../../Core/Dependencies/lib/libfreetype.a ../../Core/Dependencies/lib/liblibvorbisfile.a ../../Core/Dependencies/lib/liblibvorbis.a ../../Core/Dependencies/lib/liblibogg.a ../../Core/Dependencies/lib/libopenal.so ../../Core/Dependencies/lib/libphysfs.a ../../Core/Dependencies/lib/libpng15.a ../../Core/Dependencies/lib/libz.a -lGL -lGLU -lSDL ../../Modules/lib/libPolycode2DPhysics.a ../../Modules/Dependencies/lib/libBox2D.a ../../Modules/lib/libPolycode3DPhysics.a ../../Modules/Dependencies/lib/libBulletDynamics.a ../../Modules/Dependencies/lib/libBulletCollision.a ../../Modules/Dependencies/lib/libLinearMath.a -lX11

default: ParticleSystems 2DPhysics_Basic 2DPhysics_CollisionOnly 2DPhysics_Contacts 2DPhysics_Joints 2DPhysics_PointCollision Transforms PositionalSounds 3DBasics 3DPhysics_Basic 3DPhysics_Character 3DPhysics_CollisionOnly 3DPhysics_Contacts 3DPhysics_RayTest 3DPhysics_Vehicle MaterialsAndLights BasicImage BasicText EventHandling KeyboardInput MouseInput PlayingSounds SceneEntities SceneSprites SkeletalAnimation UpdateLoop  

clean:
	rm ParticleSystems
	rm 2DPhysics_Basic
	rm 2DPhysics_CollisionOnly
	rm 2DPhysics_Contacts
	rm 2DPhysics_Joints
	rm 2DPhysics_PointCollision
	rm Transforms
	rm PositionalSounds
	rm 3DBasics
	rm 3DPhysics_Basic
	rm 3DPhysics_Character
	rm 3DPhysics_CollisionOnly
	rm 3DPhysics_Contacts
	rm 3DPhysics_RayTest
	rm 3DPhysics_Vehicle
	rm MaterialsAndLights
	rm BasicImage
	rm BasicText
	rm EventHandling
	rm KeyboardInput
	rm MouseInput
	rm PlayingSounds
	rm SceneEntities
	rm SceneSprites
	rm SkeletalAnimation
	rm UpdateLoop

ParticleSystems:
	$(CC) $(CFLAGS) -I./Contents/ParticleSystems main.cpp Contents/ParticleSystems/HelloPolycodeApp.cpp -o ParticleSystems $(LDFLAGS)
2DPhysics_Basic:
	$(CC) $(CFLAGS) -I./Contents/2DPhysics_Basic main.cpp Contents/2DPhysics_Basic/HelloPolycodeApp.cpp -o 2DPhysics_Basic $(LDFLAGS)
2DPhysics_CollisionOnly:
	$(CC) $(CFLAGS) -I./Contents/2DPhysics_CollisionOnly main.cpp Contents/2DPhysics_CollisionOnly/HelloPolycodeApp.cpp -o 2DPhysics_CollisionOnly $(LDFLAGS)
2DPhysics_Contacts:
	$(CC) $(CFLAGS) -I./Contents/2DPhysics_Contacts main.cpp Contents/2DPhysics_Contacts/HelloPolycodeApp.cpp -o 2DPhysics_Contacts $(LDFLAGS)
2DPhysics_Joints:
	$(CC) $(CFLAGS) -I./Contents/2DPhysics_Joints main.cpp Contents/2DPhysics_Joints/HelloPolycodeApp.cpp -o 2DPhysics_Joints $(LDFLAGS)
2DPhysics_PointCollision:
	$(CC) $(CFLAGS) -I./Contents/2DPhysics_PointCollision main.cpp Contents/2DPhysics_PointCollision/HelloPolycodeApp.cpp -o 2DPhysics_PointCollision $(LDFLAGS)
2DShapes:
	$(CC) $(CFLAGS) -I./Contents/2DShapes main.cpp Contents/2DShapes/HelloPolycodeApp.cpp -o 2DShapes $(LDFLAGS)
Transforms:
	$(CC) $(CFLAGS) -I./Contents/Transforms main.cpp Contents/Transforms/HelloPolycodeApp.cpp -o Transforms $(LDFLAGS)
PositionalSounds:
	$(CC) $(CFLAGS) -I./Contents/PositionalSounds main.cpp Contents/PositionalSounds/HelloPolycodeApp.cpp -o PositionalSounds $(LDFLAGS)
3DBasics:
	$(CC) $(CFLAGS) -I./Contents/3DBasics main.cpp Contents/3DBasics/HelloPolycodeApp.cpp -o 3DBasics $(LDFLAGS)
3DPhysics_Basic:
	$(CC) $(CFLAGS) -I./Contents/3DPhysics_Basic main.cpp Contents/3DPhysics_Basic/HelloPolycodeApp.cpp -o 3DPhysics_Basic $(LDFLAGS)
3DPhysics_Character:
	$(CC) $(CFLAGS) -I./Contents/3DPhysics_Character main.cpp Contents/3DPhysics_Character/HelloPolycodeApp.cpp -o 3DPhysics_Character $(LDFLAGS)
3DPhysics_CollisionOnly:
	$(CC) $(CFLAGS) -I./Contents/3DPhysics_CollisionOnly main.cpp Contents/3DPhysics_CollisionOnly/HelloPolycodeApp.cpp -o 3DPhysics_CollisionOnly $(LDFLAGS)
3DPhysics_Contacts:
	$(CC) $(CFLAGS) -I./Contents/3DPhysics_Contacts main.cpp Contents/3DPhysics_Contacts/HelloPolycodeApp.cpp -o 3DPhysics_Contacts $(LDFLAGS)
3DPhysics_RayTest:
	$(CC) $(CFLAGS) -I./Contents/3DPhysics_RayTest main.cpp Contents/3DPhysics_RayTest/HelloPolycodeApp.cpp -o 3DPhysics_RayTest $(LDFLAGS)
3DPhysics_Vehicle:
	$(CC) $(CFLAGS) -I./Contents/3DPhysics_Vehicle main.cpp Contents/3DPhysics_Vehicle/HelloPolycodeApp.cpp -o 3DPhysics_Vehicle $(LDFLAGS)
MaterialsAndLights:
	$(CC) $(CFLAGS) -I./Contents/MaterialsAndLights main.cpp Contents/MaterialsAndLights/HelloPolycodeApp.cpp -o MaterialsAndLights $(LDFLAGS)
BasicImage:
	$(CC) $(CFLAGS) -I./Contents/BasicImage main.cpp Contents/BasicImage/HelloPolycodeApp.cpp -o BasicImage $(LDFLAGS)
BasicText:
	$(CC) $(CFLAGS) -I./Contents/BasicText main.cpp Contents/BasicText/HelloPolycodeApp.cpp -o BasicText $(LDFLAGS)
EventHandling:
	$(CC) $(CFLAGS) -I./Contents/EventHandling main.cpp Contents/EventHandling/HelloPolycodeApp.cpp -o EventHandling $(LDFLAGS)
KeyboardInput:
	$(CC) $(CFLAGS) -I./Contents/KeyboardInput main.cpp Contents/KeyboardInput/HelloPolycodeApp.cpp -o KeyboardInput $(LDFLAGS)
MouseInput:
	$(CC) $(CFLAGS) -I./Contents/MouseInput main.cpp Contents/MouseInput/HelloPolycodeApp.cpp -o MouseInput $(LDFLAGS)
PlayingSounds:
	$(CC) $(CFLAGS) -I./Contents/PlayingSounds main.cpp Contents/PlayingSounds/HelloPolycodeApp.cpp -o PlayingSounds $(LDFLAGS)
SceneEntities:
	$(CC) $(CFLAGS) -I./Contents/SceneEntities main.cpp Contents/SceneEntities/HelloPolycodeApp.cpp -o SceneEntities $(LDFLAGS)
SceneSprites:
	$(CC) $(CFLAGS) -I./Contents/SceneSprites main.cpp Contents/SceneSprites/HelloPolycodeApp.cpp -o SceneSprites $(LDFLAGS)
SkeletalAnimation:
	$(CC) $(CFLAGS) -I./Contents/SkeletalAnimation main.cpp Contents/SkeletalAnimation/HelloPolycodeApp.cpp -o SkeletalAnimation $(LDFLAGS)
UpdateLoop:
	$(CC) $(CFLAGS) -I./Contents/UpdateLoop main.cpp Contents/UpdateLoop/HelloPolycodeApp.cpp -o UpdateLoop $(LDFLAGS)
