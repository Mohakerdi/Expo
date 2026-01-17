// ==================== main.cpp (الكود التشخيصي النهائي) ====================
#include <iostream>
#include <direct.h> // For getting the current directory on Windows
#include "Application.h"

int main()
{
    // --- Diagnostic Code ---
    char current_path_buffer[256];
    _getcwd(current_path_buffer, 256);
    std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
    std::cout << "!!! DEBUG: CURRENT WORKING DIRECTORY IS: " << current_path_buffer << std::endl;
    std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
    // --- End Diagnostic Code ---

    std::cout << "MAIN START\\n";
    Application app;
    std::cout << "BEFORE RUN\\n";
    app.run();
    std::cout << "AFTER RUN\\n";
    return 0;
}

