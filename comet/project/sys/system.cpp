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
            throw SubprocessError(GetLastError());
        }

        WaitForSingleObject(processInfo.hThread, INFINITE);
        CloseHandle(processInfo.hProcess);
        CloseHandle(processInfo.hThread);
        
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

}


}