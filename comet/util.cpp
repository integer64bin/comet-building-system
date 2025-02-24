#include <fstream>

#include <util.hpp>

namespace comet {

std::string *makeStringArray(int argc, const char **argv) {
    if(!argc) {
        return nullptr;
    }
    std::string *strings = new std::string[argc];

    for(int i = 0; i < argc; i++) {
        strings[i] = argv[i];
    }

    return strings;
}

auto readFile(std::string_view path) -> std::string {
    constexpr auto read_size = std::size_t(4096);
    auto stream = std::ifstream(path.data());
    stream.exceptions(std::ios_base::badbit);

    if (!stream) {
        throw std::ios_base::failure("file does not exist");
    }
    
    auto out = std::string();
    auto buf = std::string(read_size, '\0');
    while (stream.read(& buf[0], read_size)) {
        out.append(buf, 0, stream.gcount());
    }
    out.append(buf, 0, stream.gcount());
    return out;
}


}