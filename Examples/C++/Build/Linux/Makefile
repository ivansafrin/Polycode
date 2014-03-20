CC=g++
CFLAGS=-I../../Core/Dependencies/include -I../../Core/Dependencies/include/AL -I../../Core/include -I../../Modules/include -I../../Modules/Dependencies/include -I../../Modules/Dependencies/include/bullet
LDFLAGS=-lrt -ldl -lpthread ../../Core/lib/libPolycore.a ../../Core/Dependencies/lib/libfreetype.a ../../Core/Dependencies/lib/liblibvorbisfile.a ../../Core/Dependencies/lib/liblibvorbis.a ../../Core/Dependencies/lib/liblibogg.a ../../Core/Dependencies/lib/libopenal.so ../../Core/Dependencies/lib/libphysfs.a ../../Core/Dependencies/lib/libpng15.a ../../Core/Dependencies/lib/libz.a -lGL -lGLU -lSDL ../../Modules/lib/libPolycode2DPhysics.a ../../Modules/Dependencies/lib/libBox2D.a ../../Modules/lib/libPolycode3DPhysics.a ../../Modules/Dependencies/lib/libBulletDynamics.a ../../Modules/Dependencies/lib/libBulletCollision.a ../../Modules/Dependencies/lib/libLinearMath.a

default: 2DAudio 2DParticles 2DPhysics_Basic 2DPhysics_CollisionOnly 2DPhysics_Contacts 2DPhysics_Joints 2DPhysics_PointCollision 2DShapes 2DTransforms 3DAudio 3DBasics 3DMeshParticles 3DParticles 3DPhysics_Basic 3DPhysics_Character 3DPhysics_CollisionOnly 3DPhysics_Contacts 3DPhysics_RayTest 3DPhysics_Vehicle AdvancedLighting BasicImage BasicLighting BasicText EventHandling KeyboardInput MouseInput Networking_Client Networking_Server PlayingSounds SceneEntities SceneSprites SkeletalAnimation UpdateLoop  

clean:
	rm 2DAudio
	rm 2DParticles
	rm 2DPhysics_Basic
	rm 2DPhysics_CollisionOnly
	rm 2DPhysics_Contacts
	rm 2DPhysics_Joints
	rm 2DPhysics_PointCollision
	rm 2DShapes
	rm 2DTransforms
	rm 3DAudio
	rm 3DBasics
	rm 3DMeshParticles
	rm 3DParticles
	rm 3DPhysics_Basic
	rm 3DPhysics_Character
	rm 3DPhysics_CollisionOnly
	rm 3DPhysics_Contacts
	rm 3DPhysics_RayTest
	rm 3DPhysics_Vehicle
	rm AdvancedLighting
	rm BasicImage
	rm BasicLighting
	rm BasicText
	rm EventHandling
	rm KeyboardInput
	rm MouseInput
	rm Networking_Client
	rm Networking_Server
	rm PlayingSounds
	rm SceneEntities
	rm SceneSprites
	rm SkeletalAnimation
	rm UpdateLoop

2DAudio:
	$(CC) $(CFLAGS) -I./Contents/2DAudio main.cpp Contents/2DAudio/HelloPolycodeApp.cpp -o 2DAudio $(LDFLAGS)
2DParticles:
	$(CC) $(CFLAGS) -I./Contents/2DParticles main.cpp Contents/2DParticles/HelloPolycodeApp.cpp -o 2DParticles $(LDFLAGS)
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
2DTransforms:
	$(CC) $(CFLAGS) -I./Contents/2DTransforms main.cpp Contents/2DTransforms/HelloPolycodeApp.cpp -o 2DTransforms $(LDFLAGS)
3DAudio:
	$(CC) $(CFLAGS) -I./Contents/3DAudio main.cpp Contents/3DAudio/HelloPolycodeApp.cpp -o 3DAudio $(LDFLAGS)
3DBasics:
	$(CC) $(CFLAGS) -I./Contents/3DBasics main.cpp Contents/3DBasics/HelloPolycodeApp.cpp -o 3DBasics $(LDFLAGS)
3DMeshParticles:
	$(CC) $(CFLAGS) -I./Contents/3DMeshParticles main.cpp Contents/3DMeshParticles/HelloPolycodeApp.cpp -o 3DMeshParticles $(LDFLAGS)
3DParticles:
	$(CC) $(CFLAGS) -I./Contents/3DParticles main.cpp Contents/3DParticles/HelloPolycodeApp.cpp -o 3DParticles $(LDFLAGS)
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
AdvancedLighting:
	$(CC) $(CFLAGS) -I./Contents/AdvancedLighting main.cpp Contents/AdvancedLighting/HelloPolycodeApp.cpp -o AdvancedLighting $(LDFLAGS)
BasicImage:
	$(CC) $(CFLAGS) -I./Contents/BasicImage main.cpp Contents/BasicImage/HelloPolycodeApp.cpp -o BasicImage $(LDFLAGS)
BasicLighting:
	$(CC) $(CFLAGS) -I./Contents/BasicLighting main.cpp Contents/BasicLighting/HelloPolycodeApp.cpp -o BasicLighting $(LDFLAGS)
BasicText:
	$(CC) $(CFLAGS) -I./Contents/BasicText main.cpp Contents/BasicText/HelloPolycodeApp.cpp -o BasicText $(LDFLAGS)
EventHandling:
	$(CC) $(CFLAGS) -I./Contents/EventHandling main.cpp Contents/EventHandling/HelloPolycodeApp.cpp -o EventHandling $(LDFLAGS)
KeyboardInput:
	$(CC) $(CFLAGS) -I./Contents/KeyboardInput main.cpp Contents/KeyboardInput/HelloPolycodeApp.cpp -o KeyboardInput $(LDFLAGS)
MouseInput:
	$(CC) $(CFLAGS) -I./Contents/MouseInput main.cpp Contents/MouseInput/HelloPolycodeApp.cpp -o MouseInput $(LDFLAGS)
Networking_Client:
	$(CC) $(CFLAGS) -I./Contents/Networking_Client main.cpp Contents/Networking_Client/HelloPolycodeApp.cpp -o Networking_Client $(LDFLAGS)
Networking_Server:
	$(CC) $(CFLAGS) -I./Contents/Networking_Server main.cpp Contents/Networking_Server/HelloPolycodeApp.cpp -o Networking_Server $(LDFLAGS)
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
