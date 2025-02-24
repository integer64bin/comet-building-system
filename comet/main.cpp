#include <iostream>

#include <comet.hpp>


int main(int argc, const char **argv) {

    comet::Projects::init();

    comet::console::parseArguments(
        argc,
        argv
    );

    comet::Projects::finalize();

    // std::string src = read_file(".xconfig");

    // comet::Lexer lexer(src);

    // auto list = lexer.tokenize();

    // for(auto tok : list) {
    //     std::cout << tok << std::endl;
    // }

    // comet::Parser parser(list);

    // comet::Script script = parser.parse();

    // script.execute();

    getchar();

    return 0;
}