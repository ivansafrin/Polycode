
#include "PolycodeLUA.h"
#include "PolycodeLUA2D.h"

int luaopen_Polycode(lua_State *L) {
	static const struct luaL_reg polycodeLib [] = {
		//Screen
		{"Screen", Polycore_Screen},
		{"Screen_addChild", Polycore_Screen_addChild},
		{"Screen_removeChild", Polycore_Screen_removeChild},
		{"Screen_setScreenOffset", Polycore_Screen_setScreenOffset},
		{"Screen_getScreenOffset", Polycore_Screen_getScreenOffset},
		{"Screen_setScreenShader", Polycore_Screen_setScreenShader},
		{"Screen_getHighestZIndex", Polycore_Screen_getHighestZIndex},
		{"Screen_sortChildren", Polycore_Screen_sortChildren},
		{"Screen_hasFilterShader", Polycore_Screen_hasFilterShader},
		{"Screen_setEnabled", Polycore_Screen_setEnabled},
		{"Screen_getEnabled", Polycore_Screen_getEnabled},
		
		{"ScreenImage", Polycore_ScreenImage},
		{"ScreenImage_setRotation", Polycore_ScreenImage_setRotation},				
		{NULL, NULL}  /* sentinel */
	};
	luaL_openlib(L, "Polycore", polycodeLib, 0);
	return 1;	
}