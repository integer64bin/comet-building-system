#pragma once

#include <string>
#include <list>

namespace comet {

struct Configs;

class Compiler {

public:

    /*================================Methods================================*/

    Compiler() = delete;
    Compiler(const Compiler &) = delete;
    Compiler(const Compiler &&) = delete;


    /*============================Static utilities===========================*/

    // Compilation
    // -c -o
    // configs stores information such as headers, sources, 
    // 
    static void compile(Configs &configs, std::string target, std::string out = "");

    // Linking
    // -o
    static void link(Configs &c, std::list<std::string> files);

private:
    

};




}