#include "timestamp.h"

using namespace utils::literals;

using timestamp_s = utils::timestamp<utils::seconds>;
using timestamp_ms = utils::timestamp<utils::milliseconds>;
using timestamp_us = utils::timestamp<utils::microseconds>;

int main(int argc, char const *argv[]) {
    
    timestamp_us ts_us(1'725'648);
    std::cout << "Timestamp value: " << ts_us << std::endl;

    timestamp_s ts_s = ts_us;
    std::cout << "Timestamp value: " << ts_s << std::endl;

    timestamp_ms ts_ms = ts_s;
    std::cout << "Timestamp value: " << ts_ms << std::endl;

    timestamp_ms ts_literal = 1700_ms;
    std::cout << "Timestamp value: " << ts_literal << std::endl;

    std::cout << ts_us << " - " << ts_literal << " = " << (ts_us - ts_literal) << std::endl;
    std::cout << ts_us << " + " << ts_literal << " = " << (ts_us + ts_literal) << std::endl;
    std::cout << ts_us << " is " << ((ts_us > ts_literal) ? "greater than " : ((ts_us < ts_literal) ? "smaller than " : "equal to ")) << ts_literal << std::endl;

    timestamp_us ts_compare = 5'000_us;
    std::cout << "(" << ts_us << " - " << ts_literal << ") is ";
    if ((ts_us - ts_literal) > ts_compare) {
        std::cout << "greater than " << ts_compare << std::endl;
    } else {
        std::cout << "smaller than or equal to " << ts_compare << std::endl;
    }

    return 0;
}

