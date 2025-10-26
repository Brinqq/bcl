#include <stdio.h>

// oprhan headers so clangd doesnt complain about missing compilation data base info on header only libs.
#include "bl/containers/densetable.h" // IWYU pragma: keep
#include "bl/containers/tagptr.h" // IWYU pragma: keep
#include "bl/containers/vector.h" // IWYU pragma: keep
#include "bl/containers/freelist.h" // IWYU pragma: keep
#include "bl/containers/pool.h" // IWYU pragma: keep
#include "bl/containers/vector.h" // IWYU pragma: keep
#include "bl/containers/pool.h" // IWYU pragma: keep
#include "bl/memory/virtualallocator.h" // IWYU pragma: keep

#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest/doctest.h"

//enabled test_modules
#include "headers/densetable_test.h" // IWYU pragma: keep

int main(int argc, char** argv) {
    doctest::Context context;
    context.addFilter("test-case-exclude", "*math*"); // exclude test cases with "math" in their name
    context.setOption("abort-after", 5);              // stop test execution after 5 failed assertions
    context.setOption("order-by", "name");            // sort the test cases by their name
    context.applyCommandLine(argc, argv);
    context.setOption("no-breaks", true);             // don't break in the debugger when assertions fail
    int res = context.run(); // run
    if(context.shouldExit()) // important - query flags (and --exit) rely on the user doing this
        return res;          // propagate the result of the tests
    int client_stuff_return_code = 0;
    return res + client_stuff_return_code; // the result from doctest is propagated here as well
}
