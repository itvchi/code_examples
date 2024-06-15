#include "return_code.h"

#include <iostream>

int main(int argc, char const *argv[]) {
    
    /* Constructor tests */
    return_code none;
    return_code from_error_code{return_code::Ok};
    return_code from_return_code{from_error_code};

    std::cout << "--- Constructor tests: ---" << std::endl;
    std::cout << "return_code none: " << none << std::endl;
    std::cout << "return_code from_error_code: " << from_error_code << std::endl;
    std::cout << "return_code from_return_code: " << from_return_code << std::endl;

    return 0;
}

