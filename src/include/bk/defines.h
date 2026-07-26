#pragma once
#include <stddef.h>
#include <assert.h>

namespace bk{

/**
 * \breif empty class.
*  \note the only reason we dont use std::monostate is because the minimum std version is 17.
*  \code
*   std::conditional_t(bool, SomeStruct, bcl::monostate);
*  \endcode
*/
struct Monostate{};

}
