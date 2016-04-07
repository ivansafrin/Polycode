CC=g++
INCDIR=../include/
SRCDIR=../src/lua/
PYTHON_EXECUTABLE=python

CFLAGS=-I$(INCDIR)

default:
	$(PYTHON_EXECUTABLE) create_lua_library/create_lua_library.py $(INCDIR)polycode/core/ Polycode Polycode.h polycore Polycore lua/core/API lua/core/API/Polycode $(INCDIR)polycode/lua/core $(SRCDIR)core
	@echo "\033[1;32mBuilding \033[0m[\033[1;33m$(SRCDIR)core/PolycodeLUA.cpp\033[0m]"
	@$(CC) $(CFLAGS) -c $(SRCDIR)core/PolycodeLUA.cpp -o $(SRCDIR)core/PolycodeLUA.o
	
all: default modules

modules:
	#$(PYTHON_EXECUTABLE) create_lua_library/create_lua_library.py $(INCDIR)polycode/modules/physics2D/ Physics2D polycode/modules/physics2D/Polycode2DPhysics.h physics2d Physics2D lua/physics2D/API lua/physics2D/API/Physics2D $(INCDIR)polycode/lua/physics2D $(SRCDIR)physics2D
	#@echo "\033[1;32mBuilding \033[0m[\033[1;33m$(SRCDIR)physics2D/Physics2DLUA.cpp\033[0m]"
	#@$(CC) $(CFLAGS) -c $(SRCDIR)physics2D/Physics2DLUA.cpp -o $(SRCDIR)physics2D/Physics2DLUA.o
	$(PYTHON_EXECUTABLE) create_lua_library/create_lua_library.py $(INCDIR)polycode/modules/physics3D/ Physics3D polycode/modules/physics3D/Polycode3DPhysics.h physics3d Physics3D lua/physics3D/API lua/physics3D/API/Physics3D $(INCDIR)polycode/lua/physics3D $(SRCDIR)physics3D
	@echo "\033[1;32mBuilding \033[0m[\033[1;33m$(SRCDIR)physics3D/Physics3DLUA.cpp\033[0m]"
	@$(CC) $(CFLAGS) -c $(SRCDIR)physics3D/Physics3DLUA.cpp -o $(SRCDIR)physics3D/Physics3DLUA.o
	$(PYTHON_EXECUTABLE) create_lua_library/create_lua_library.py $(INCDIR)polycode/modules/ui/ UI polycode/modules/ui/PolycodeUI.h ui UI lua/ui/API lua/ui/API/UI $(INCDIR)polycode/lua/ui $(SRCDIR)ui
	@echo "\033[1;32mBuilding \033[0m[\033[1;33m$(SRCDIR)ui/UILUA.cpp\033[0m]"
	@$(CC) $(CFLAGS) -c $(SRCDIR)ui/UILUA.cpp -o $(SRCDIR)ui/UILUA.o
