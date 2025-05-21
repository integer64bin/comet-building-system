#include <project\sys\system.hpp>

#include <iostream>
#include <windows.h>

#include <map>

#include <exception\console\SubprocessError.hpp>


namespace comet {

namespace system {

    std::map<int, std::string> ERRORS_MESSAGES;

    bool createProcess(std::string name, std::string args) {
        
        STARTUPINFO si;
        PROCESS_INFORMATION processInfo;

        ZeroMemory( &si, sizeof(si) );
        si.cb = sizeof(si);
        ZeroMemory( &processInfo, sizeof(processInfo) );

        std::string command = (name + ' ' + args);

        char* cstrCommand = new char[command.size() + 1];

        command.copy(cstrCommand, command.size());
        cstrCommand[command.size()] = 0;

        // create:
        if(!CreateProcess(
            NULL,           // No module name (use command line)
            cstrCommand,    // Command line
            NULL,           // Process handle not inheritable
            NULL,           // Thread handle not inheritable
            FALSE,          // Set handle inheritance to FALSE
            0,              // No creation flags
            NULL,           // Use parent's environment block
            NULL,           // Use parent's starting directory 
            &si,            // Pointer to STARTUPINFO structure
            &processInfo)   // Pointer to PROCESS_INFORMATION structure
        ) {
            int errorCode = GetLastError();
            std::cout << errorCode << std::endl;
            if(errorCode == 0) {
                std::cout << "Retrying..." << std::endl;
                // goto create;
            }
            delete[] cstrCommand;
            throw SubprocessError(errorCode);
        }

        WaitForSingleObject(processInfo.hThread, INFINITE);
        CloseHandle(processInfo.hProcess);
        CloseHandle(processInfo.hThread);
        
        delete[] cstrCommand;

        return true;
    }

    void init() {

        ERRORS_MESSAGES.emplace(
            0, "No error"
        );

        ERRORS_MESSAGES.emplace(
            1, "Incorrect fuction"
        );

        ERRORS_MESSAGES.emplace(
            2, "The system cannot find the file specified"
        );

        ERRORS_MESSAGES.emplace(
            87, "The parameter is incorrect"
        );


    }

    void finalize() {

    }

    std::string identifyErrorCode(int code) {
        if(ERRORS_MESSAGES.contains(code))
            return ERRORS_MESSAGES.at(code);
        return "Unknow error";
    }

    namespace ui {

        void setFontColor(color foreground, color background) {
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

            SetConsoleTextAttribute(hConsole, (background << 4) | foreground);
        }

    }

}


}