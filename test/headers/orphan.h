#pragma once

//this forces clangd to propely resolve development header files we havent include in a source file/never added to compilation database.
//due to the forced absolute path not working for some reason that i dont care to fix.

//containers
#include "bk/containers/tagptr.h"
#include "bk/containers/vector.h"
