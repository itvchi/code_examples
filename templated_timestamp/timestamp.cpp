#include "timestamp.h"
#include <type_traits>

namespace utils {

    template<typename T>
    timestamp<T>::timestamp(long long value) : value_(value) {

    }

    template<typename T>
    std::string timestamp<T>::format(long long value) {

        std::string                             str{std::to_string(value)};
        int                                     insertPosition{static_cast<int>(str.length()) - 3};
        
        while (insertPosition > 0) {
            str.insert(insertPosition, "'");
            insertPosition -= 3;
        }

        return str;
    }

    /* Explicit template instantiations */
    template class timestamp<seconds>;
    template class timestamp<milliseconds>;
    template class timestamp<microseconds>;


    /* Literal operators */
    namespace literals {

        timestamp<seconds> operator"" _s(unsigned long long value) {
            return timestamp<seconds>(value);
        }

        timestamp<milliseconds> operator"" _ms(unsigned long long value) {
            return timestamp<milliseconds>(value);
        }

        timestamp<microseconds> operator"" _us(unsigned long long value) {
            return timestamp<microseconds>(value);
        }
    }
};