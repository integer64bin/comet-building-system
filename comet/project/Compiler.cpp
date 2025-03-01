#include <project\project.hpp>

#include <iostream>

#include <project\sys\system.hpp>

#include <exception\console\SubprocessError.hpp>

namespace comet {

/*==================================Variables=================================*/

bool Compiler::debug_info    = false;

bool Compiler::ignore_errors = false;

size_t Compiler::erros_count = 0;

/*==========================Methods' implementations==========================*/

void Compiler::compile(CompilerOptions &opts, std::string src, std::string out) {
    std::string arguments;
    
    if(!opts.includes.empty()) {
        std::string inclFlag = getIncludeFlags(opts.includes, "");

        arguments.append(inclFlag);

    }
    
    if(!opts.flags.empty())
        arguments.append(opts.flags);
    if(out.empty()) {
        arguments.append(" -c ")
                 .append(src);
    } else {
        arguments.append(" -c -o ")
                 .append(src + ' ')
                 .append(out);
    }
    
    
    if(debug_info)
        std::cout << opts.compiler << ' ' << arguments << std::endl;

    try {
        system::createProcess(opts.compiler, arguments);
    } catch(SubprocessError e) {
        if(!ignore_errors) {
            std::cerr << "An error occured during building" << std::endl;
            std::cerr << e.what() << std::endl;
            std::cerr << "Compilation interrupted" << std::endl;
            std::exit(1);
        } else {
            std::cerr << "An error occured during building" << std::endl;
            std::cerr << e.what() << std::endl;
            std::cout << "Compilation continues" << std::endl;
            erros_count++;
            return;
        }
    }
}

// Linking
// -o
void Compiler::link(CompilerOptions &opts, std::list<std::string> files, bool sources) {
    if(erros_count) {
        std::cout << "Linking don't performs, because errors "
        "occured during compiltion" << std::endl;
        std::exit(1);
    }
    if(sources) {

    }


    if(!opts.dllSearchingPaths.empty()) {

    }

}



std::string Compiler::getFlags(std::list<std::string> flags) {
    std::string result;

    for(auto flg : flags) {
        result.append(flg).push_back(' ');
    }

    return result;
}



std::string Compiler::getFlags(std::initializer_list<std::string> flags) {
    std::string result;

    for(auto flg : flags) {
        result.append(flg).push_back(' ');
    }

    return result;
}

std::string Compiler::getIncludeFlags(const std::list<std::string> &includes,
                            const std::string root) {
    std::string inclFlag;
    for(auto includeDirectory : includes) {
        inclFlag.append("-I\"")
                // .append(root + "\\")
                .append(includeDirectory)
                .append("\" ");
    }
    return inclFlag;
}


}