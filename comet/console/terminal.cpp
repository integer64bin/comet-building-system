#include <console\console.hpp>

#include <iostream>

namespace comet {

namespace console {

    extern std::vector<std::string> arguments;

    void readCommand();

    void terminal() {
        std::cout << "Terminal mode activated, for exit enter commad exit/quit\n";
        std::cout << "In this mode you can use command without \"comet\" prefix" << std::endl;
        
        readCommand();
        std::cout << "Terminal halted\nBuy" << std::endl;
        std::exit(0);
    }

    void readCommand() {
        std::string buffer;
        
        while(true) {
            std::cout << "comet > ";
            std::getline(std::cin, buffer);
            if(buffer.empty())
                continue;
            // terminal commands
            if(buffer.compare("quit") == 0 || buffer.compare("exit") == 0)
                break;
            // else if(buffer.compare("cls")) {
            //     system("cls");
            //     continue;
            // }
            parseCommand(buffer);
        }
    }

}


}