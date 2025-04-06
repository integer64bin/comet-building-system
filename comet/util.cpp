#include <util.hpp>

#include <fstream>
#include <iostream>

namespace comet {

namespace fs = std::filesystem;

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

std::vector<std::string> makeStringVector(int argc, const char **argv) {
    std::vector<std::string> strings(argc);

    for(int i = 0; i < argc; i++) {
        strings[i] = argv[i];
    }

    return strings;
}

std::list<std::string> makeStringList(int argc, const char **argv) {
    std::list<std::string> result;
    for(int i = 0; i < argc; i++) {
        result.push_back(argv[i]);
    }
    return result;
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
    while (stream.read(&buf[0], read_size)) {
        out.append(buf, 0, stream.gcount());
    }
    out.append(buf, 0, stream.gcount());
    return out;
}



std::string getSeparatedNumber(std::size_t number, int sep) {
    
    std::string result;

    while(number != 0) {
        result.insert(0, " ");
        std::string num = std::to_string(number % sep);
        if(num.size() < 3 && (number / sep) != 0) {
            num.insert(0, std::string(3ULL-num.size(), '0'));
        } 
        result.insert(0, num);
        number /= sep;
    }
    return result;
}



std::list<fs::path> getFiles(std::string path) {
    std::list<fs::path> files;
    for(const auto &entry : fs::directory_iterator(path)) {
        if(fs::is_directory(entry)) {
            files.merge(getFiles(entry.path().string()));
            continue;
        }
        files.push_back(entry.path());
    }
    return files;
}


}