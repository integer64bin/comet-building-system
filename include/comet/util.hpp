#pragma once

#include <string>
#include <vector>

#include <token\Token.hpp>

namespace comet {


std::string *makeStringArray(int argc, const char **argv);

std::vector<std::string> makeStringVector(int argc, const char **argv);

auto readFile(std::string_view path) -> std::string;


}