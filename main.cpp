#include "stdafx.h"

int main() {
    fractal::Display disp;
    try {
        disp.run();
    } catch (std::exception e) {
        std::cout << "Runtime error\n";
        std::cout << e.what();
    }
    
    return 0;
}