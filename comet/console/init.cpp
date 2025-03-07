#include <console\console.hpp>

#include <fstream>
#include <filesystem>

namespace comet {

namespace console {

    namespace fs = std::filesystem;

    void init(fs::path where) {
        where.append("\\.xconfig");
        // If file exists do nothing
        if(fs::exists(where))
            return;
        // Else
        // Opening the file in append mode
        // and adding commet
        std::ofstream xconfigFile(where, std::ios_base::app);
        xconfigFile << "# Write your script here..." << std::endl;
        
        xconfigFile.close();
    }


}


}