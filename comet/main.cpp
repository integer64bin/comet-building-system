#include <iostream>

#include <comet.hpp>

#include <project\sys\system.hpp>

int main(int argc, const char **argv) {

    comet::init();

    comet::console::parseArguments(
        argc,
        argv
    );

    comet::finalize();

    return 0;
}