#include <project\project.hpp>

#include <project\sys\system.hpp>

#include <iostream>

namespace comet {


std::string getIncludeFlags(const std::list<std::string> &includes, 
                            const std::string root);


/*==========================Methods' implementations==========================*/

void Compiler::compile(CompilerOptions &opts, std::string src, std::string out) {
    std::string options;
    
    if(!opts.includes.empty()) {
        std::string inclFlag = getIncludeFlags(opts.includes, "");

        options.append(inclFlag);

    }

    /// \todo libraries
    
    options.append(opts.flags)
           .append(" -c -o ")
           .append(src + ' ')
           .append(out);

    std::cout << options << std::endl;

    system::createProcess("g++", options);

}

// Linking
// -o
void Compiler::link(CompilerOptions &opts, std::list<std::string> files) {

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

std::string getIncludeFlags(const std::list<std::string> &includes,
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