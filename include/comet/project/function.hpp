#pragma once

#include <string>

namespace comet {

    namespace functions {

        constinit const std::string_view F_PROJECT             = "project";

        constinit const std::string_view F_SET_ROOT            = "setRoot";

        constinit const std::string_view F_SET_COMPILER        = "setCompiler";

        constinit const std::string_view F_ADD_SOURCES_PATH    = "addSourcesPath";

        constinit const std::string_view F_ADD_INCLUDES        = "addIncludes";

        constinit const std::string_view F_ADD_LIBRARIES       = "addLibraries";

        constinit const std::string_view F_SET_OUT_PATH        = "setOutPath";

        constinit const std::string_view F_SET_EXECUTABLE      = "setExecutable";
        
        constinit const std::string_view F_SET_EXECUTABLE_PATH = "setExecutablePath";

    }


}