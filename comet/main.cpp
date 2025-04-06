#include <iostream>

#include <vector>

#include <functional>

#include <comet.hpp>

int main(int argc, const char **argv) {

    comet::init();

    comet::console::parseArguments(
        argc,
        argv
    );

    comet::finalize();

    return 0;
}