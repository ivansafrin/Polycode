#pragma once
#include <Polycode.h>
#include <memory>

extern "C" {
	
 #include <stdio.h>
 #include "duktape.h"

int _PolyExport jsopen_Polycode(duk_context *ctx);

}
