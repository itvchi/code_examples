#ifndef _TIMESTAMP_H_
#define _TIMESTAMP_H_

#include <iostream>

namespace utils {
    struct seconds {
        static constexpr int precision = 1;
        static const char* unit() { return "s"; }
    };

    struct milliseconds {
        static constexpr int precision = 1000;
        static const char* unit() { return "ms"; }
    };

    struct microseconds {
        static constexpr int precision = 1000000;
        static const char* unit() { return "us"; }
    };

    template <typename From, typename To>
    struct precision_conversion {
        static constexpr double value = static_cast<double>(To::precision) / From::precision;
    };

    template<typename T>
    class timestamp {
        public:
            explicit timestamp(long long value);

            template<typename U>
            operator timestamp<U>() const {
                long long new_value = static_cast<long long>(value_ * precision_conversion<T, U>::value);
                return timestamp<U>(new_value);
            }

            long long get() const { 
                return value_; 
            }

            const char* unit() const {
                return T::unit();
            }

        private:
            long long value_;

            static std::string format(long long value);

            template<typename U>
            friend std::ostream& operator<<(std::ostream& os, const timestamp<U>& ts);
    };

    template<typename T>
    std::ostream& operator<<(std::ostream& os, const timestamp<T>& ts) {
        return os << timestamp<T>::format(ts.value_) << " " << ts.unit();
    }
}

#endif /* _TIMESTAMP_H_ */