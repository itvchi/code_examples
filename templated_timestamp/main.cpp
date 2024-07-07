#include "timestamp.h"

using namespace utils::literals;

int main(int argc, char const *argv[]) {
    
    utils::timestamp<utils::microseconds> ts_us(1'725'648);
    std::cout << "Timestamp value: " << ts_us << std::endl;

    utils::timestamp<utils::seconds> ts_s = ts_us;
    std::cout << "Timestamp value: " << ts_s << std::endl;

    utils::timestamp<utils::milliseconds> ts_ms = ts_s;
    std::cout << "Timestamp value: " << ts_ms << std::endl;

    utils::timestamp<utils::milliseconds> ts_literal = 1700_ms;
    std::cout << "Timestamp value: " << ts_literal << std::endl;

    std::cout << ts_us << " - " << ts_literal << " = " << (ts_us - ts_literal) << std::endl;
    std::cout << ts_us << " + " << ts_literal << " = " << (ts_us + ts_literal) << std::endl;

    return 0;
}

