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

    /* Operator tests */
    return_code ok{return_code::Ok};
    return_code ok_copy = ok;
    return_code error{return_code::Error};

    std::cout << "--- Operator tests: ---" << std::endl;
    std::cout << "bool operator==(const return_code& rc) test: " << ((ok == ok_copy) ? "passed" : "failed") << std::endl;
    std::cout << "bool operator==(const return_code& rc) test: " << ((ok == error) ? "failed" : "passed") << std::endl;
    std::cout << "bool operator!=(const return_code& rc) test: " << ((ok != ok_copy) ? "failed" : "passed") << std::endl;
    std::cout << "bool operator!=(const return_code& rc) test: " << ((ok != error) ? "passed" : "failed") << std::endl;
    std::cout << "bool operator==(const rerror_code ec) test: " << ((error == return_code::Error) ? "passed" : "failed") << std::endl;
    std::cout << "bool operator==(const rerror_code ec) test: " << ((error == return_code::Ok) ? "failed" : "passed") << std::endl;
    std::cout << "bool operator!=(const rerror_code ec) test: " << ((error != return_code::Error) ? "failed" : "passed") << std::endl;
    std::cout << "bool operator!=(const rerror_code ec) test: " << ((error != return_code::Ok) ? "passed" : "failed") << std::endl;
    std::cout << "operator bool() test: " << ((ok) ? "passed" : "failed") << std::endl;

    return 0;
}

