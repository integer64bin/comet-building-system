#pragma once

#include <string>
#include <vector>
#include <list>
#include <filesystem>

#include <token\Token.hpp>

namespace comet {

namespace fs = std::filesystem;

std::string *makeStringArray(int argc, const char **argv);

std::vector<std::string> makeStringVector(int argc, const char **argv);

auto readFile(std::string_view path) -> std::string;

std::string getSeparatedNumber(std::size_t s, int sep = 1000);

std::list<fs::path> getFiles(std::string path);


}