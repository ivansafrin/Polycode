INCLUDE(FindPythonModule)

FIND_PACKAGE(PythonInterp REQUIRED)

ADD_CUSTOM_COMMAND(
OUTPUT luaGenerateDocsCmd
COMMAND ${PYTHON_EXECUTABLE} make_html.py
WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
)

ADD_CUSTOM_TARGET(PolycodeLuaGenerateDocs
	DEPENDS Polycore PolycodeLuaGenerate luaGenerateDocsCmd
	COMMENT "Generating Lua Documentation"
	SOURCES make_html.py)

