DIR=../include/polycode/core/
FILES=$(DIR)PolyEntity.h $(DIR)PolySceneMesh.h

cldoc-mac:
	mkdir -p cldoc
	cldoc generate -I../include/ -isysroot /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.10.sdk -- --static --output=cldoc --language=c++ $(FILES)

