#pragma once
#include <Polycode.h>
extern "C" {
	
 #include <stdio.h>
 #include "duktape.h"

int _PolyExport jsopen_Polycode(duk_context *ctx);

}
