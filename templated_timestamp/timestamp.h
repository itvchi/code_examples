#ifndef _TIMESTAMP_H_
#define _TIMESTAMP_H_

#include <iostream>
#include <type_traits>

namespace utils {
    struct seconds {
        static constexpr unsigned int precision = 1;
        static const char* unit() { return "s"; }
    };

    struct milliseconds {
        static constexpr unsigned int precision = 1000;
        static const char* unit() { return "ms"; }
    };

    struct microseconds {
        static constexpr unsigned int precision = 1000000;
        static const char* unit() { return "us"; }
    };

    // Custom type trait to determine the common type
    template <typename T, typename U>
    struct common_time_unit {
        using type = std::conditional_t<(T::precision > U::precision), T, U>;
    };

    template <typename T, typename U>
    using common_time_unit_t = typename common_time_unit<T, U>::type;

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

            template<typename U>
            timestamp<common_time_unit_t<T, U>> operator-(const timestamp<U>& rhs) const {
                using common_t = common_time_unit_t<T, U>;
                timestamp<common_t> lhs_converted = *this;
                timestamp<common_t> rhs_converted = rhs;
                int result_value = lhs_converted.get() - rhs_converted.get();
                return timestamp<common_t>(result_value);
            }

            template<typename U>
            timestamp<common_time_unit_t<T, U>> operator+(const timestamp<U>& rhs) const {
                using common_t = common_time_unit_t<T, U>;
                timestamp<common_t> lhs_converted = *this;
                timestamp<common_t> rhs_converted = rhs;
                int result_value = lhs_converted.get() + rhs_converted.get();
                return timestamp<common_t>(result_value);
            }

            template<typename U>
            bool operator<(const timestamp<U>& rhs) const {
                using common_t = common_time_unit_t<T, U>;
                timestamp<common_t> lhs_converted = *this;
                timestamp<common_t> rhs_converted = rhs;
                return (lhs_converted.get() < rhs_converted.get());
            }

            template<typename U>
            bool operator>(const timestamp<U>& rhs) const {
                using common_t = common_time_unit_t<T, U>;
                timestamp<common_t> lhs_converted = *this;
                timestamp<common_t> rhs_converted = rhs;
                return (lhs_converted.get() > rhs_converted.get());
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

    namespace literals {

        timestamp<seconds> operator"" _s(unsigned long long value);
        timestamp<milliseconds> operator"" _ms(unsigned long long value);
        timestamp<microseconds> operator"" _us(unsigned long long value);
    };
}

#endif /* _TIMESTAMP_H_ */