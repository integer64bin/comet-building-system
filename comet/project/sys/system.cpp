#include <project\sys\system.hpp>

#include <iostream>
#include <windows.h>

namespace comet {

namespace system {

    bool createProcess(std::string name, std::string args) {
        STARTUPINFO si;
        PROCESS_INFORMATION processInfo;


        ZeroMemory( &si, sizeof(si) );
        si.cb = sizeof(si);
        ZeroMemory( &processInfo, sizeof(processInfo) );

        char* command = const_cast<char*>( (name + ' ' + args).c_str() );

        if( !CreateProcess( NULL,   // No module name (use command line)
            command,        // Command line
            NULL,           // Process handle not inheritable
            NULL,           // Thread handle not inheritable
            FALSE,          // Set handle inheritance to FALSE
            0,              // No creation flags
            NULL,           // Use parent's environment block
            NULL,           // Use parent's starting directory 
            &si,            // Pointer to STARTUPINFO structure
            &processInfo)            // Pointer to PROCESS_INFORMATION structure
        ) {
            std::cerr << "CreateProcess failed (" << GetLastError() << ')' << std::endl;
            return false;
        }

        WaitForSingleObject(processInfo.hThread, INFINITE);
        CloseHandle(processInfo.hProcess);
        CloseHandle(processInfo.hThread);
        
        return true;
    }


}


}