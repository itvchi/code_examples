#include "timestamp.h"

int main(int argc, char const *argv[]) {
    
    utils::timestamp<utils::microseconds> ts_us(1'725'648);
    std::cout << "Timestamp value: " << ts_us << std::endl;

    utils::timestamp<utils::seconds> ts_s = ts_us;
    std::cout << "Timestamp value: " << ts_s << std::endl;

    utils::timestamp<utils::milliseconds> ts_ms = ts_s;
    std::cout << "Timestamp value: " << ts_ms << std::endl;

    return 0;
}

