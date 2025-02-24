#include <project\sys\system.hpp>

#include <iostream>
#include <windows.h>

namespace comet {

namespace system {

    bool createProcess(std::string name, std::string args) {
        STARTUPINFO si;
        PROCESS_INFORMATION pi;


        ZeroMemory( &si, sizeof(si) );
        si.cb = sizeof(si);
        ZeroMemory( &pi, sizeof(pi) );

        char* command = const_cast<char*>( (name + " " + args).c_str() );

        if( !CreateProcess( nullptr,   // No module name (use command line)
            command,        // Command line
            nullptr,           // Process handle not inheritable
            nullptr,           // Thread handle not inheritable
            false,          // Set handle inheritance to FALSE
            0,              // No creation flags
            nullptr,           // Use parent's environment block
            nullptr,           // Use parent's starting directory 
            &si,            // Pointer to STARTUPINFO structure
            &pi)           // Pointer to PROCESS_INFORMATION structure
        ) {
            std::cerr << "CreateProcess failed (" << GetLastError() << ')' << std::endl;
            return false;
        }
        return true;
    }


}


}