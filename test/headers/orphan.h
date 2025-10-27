#pragma once

//this forces clangd to propely resolve development header files we havent include in a source file/never added to compilation database.
//due to the forced absolute path not working for some reason that i dont care to fix.

//containers
#include "bcl/containers/densetable.h"
#include "bcl/containers/tagptr.h"
#include "bcl/containers/vector.h"
#include "bcl/containers/freelist.h"
#include "bcl/containers/pool.h"
