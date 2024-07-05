#include "timestamp.h"

template<typename T>
utils::timestamp<T>::timestamp(long long value) : value_(value) {

}

template<typename T>
std::string utils::timestamp<T>::format(long long value) {

    std::string                             str{std::to_string(value)};
    int                                     insertPosition{static_cast<int>(str.length()) - 3};
    
    while (insertPosition > 0) {
        str.insert(insertPosition, "'");
        insertPosition -= 3;
    }

    return str;
}

/* Explicit template instantiations */
template class utils::timestamp<utils::seconds>;
template class utils::timestamp<utils::milliseconds>;
template class utils::timestamp<utils::microseconds>;