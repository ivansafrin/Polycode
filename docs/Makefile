DIR=../include/polycode/core/

HEADERS = $(wildcard ../include/polycode/core/*.h)
SOURCES = $(wildcard ../src/core/*.cpp)

HEADERS := $(filter-out ../include/polycode/core/PolyRPICore.h, $(HEADERS))
HEADERS := $(filter-out ../include/polycode/core/PolySDLCore.h, $(HEADERS))
HEADERS := $(filter-out ../include/polycode/core/PolyUWPCore.h, $(HEADERS))
HEADERS := $(filter-out ../include/polycode/core/PolyWinCore.h, $(HEADERS))
HEADERS := $(filter-out ../include/polycode/core/PolyCocoaCore.h, $(HEADERS))
HEADERS := $(filter-out ../include/polycode/core/PolyIOSCore.h, $(HEADERS))
HEADERS := $(filter-out ../include/polycode/core/PolyXAudio2AudioInterface.h, $(HEADERS))

SOURCES := $(filter-out ../src/core/PolyRPICore.cpp, $(SOURCES))
SOURCES := $(filter-out ../src/core/PolySDLCore.cpp, $(SOURCES))
SOURCES := $(filter-out ../src/core/PolyUWPCore.cpp, $(SOURCES))
SOURCES := $(filter-out ../src/core/PolyWinCore.cpp, $(SOURCES))
SOURCES := $(filter-out ../src/core/tinystr.cpp, $(SOURCES))
SOURCES := $(filter-out ../src/core/PolyXAudio2AudioInterface.cpp, $(SOURCES))


cldoc-mac:
	mkdir -p cldoc
	cldoc generate -DCLDOC -I../include/ -isysroot /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.11.sdk --  --static --output=cldoc --language=c++ $(SOURCES) $(HEADERS)

