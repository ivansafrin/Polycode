default: basic_image basic_text 2d_transforms 2d_shapes screen_entities screen_sprites basic_lighting advanced_lighting 3d_audio skeletal_animation

basic_image:
	g++ -g `freetype-config --cflags` -IBasicImage -lPolyCore BasicImage/HelloPolycodeApp.cpp main.cpp -o basic_image
basic_text:
	g++ -g `freetype-config --cflags` -IBasicText -lPolyCore BasicText/HelloPolycodeApp.cpp main.cpp -o basic_text
2d_transforms:
	g++ -g `freetype-config --cflags` -I2DTransforms -lPolyCore 2DTransforms/HelloPolycodeApp.cpp main.cpp -o 2d_transforms
2d_shapes:
	g++ -g `freetype-config --cflags` -I2DShapes -lPolyCore 2DShapes/HelloPolycodeApp.cpp main.cpp -o 2d_shapes
screen_entities:
	g++ -g `freetype-config --cflags` -IScreenEntities -lPolyCore ScreenEntities/HelloPolycodeApp.cpp main.cpp -o screen_entities
screen_sprites:
	g++ -g `freetype-config --cflags` -IScreenSprites -lPolyCore ScreenSprites/HelloPolycodeApp.cpp main.cpp -o screen_sprites
basic_lighting:
	g++ -g `freetype-config --cflags` -IBasicLighting -lPolyCore BasicLighting/HelloPolycodeApp.cpp main.cpp -o basic_lighting
advanced_lighting:
	g++ -g `freetype-config --cflags` -IAdvancedLighting -lPolyCore AdvancedLighting/HelloPolycodeApp.cpp main.cpp -o advanced_lighting
3d_audio:
	g++ -g `freetype-config --cflags` -I3DAudio -lPolyCore 3DAudio/HelloPolycodeApp.cpp main.cpp -o 3d_audio
skeletal_animation:
	g++ -g `freetype-config --cflags` -ISkeletalAnimation -lPolyCore SkeletalAnimation/HelloPolycodeApp.cpp main.cpp -o skeletal_animation
clean:
	rm basic_image basic_text 2d_transforms 2d_shapes screen_entities screen_sprites basic_lighting advanced_lighting 3d_audio skeletal_animation
