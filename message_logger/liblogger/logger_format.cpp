#include "logger_format.h"

logger_format& logger_format::operator<<(const logger_format& rhs) {

    format.insert(format.end(), rhs.format.begin(), rhs.format.end());
    return *this;
}

logger_format& logger_format::operator<<(const type& rhs) {

    format.push_back(rhs);
    return *this;
}

logger_format& logger_format::operator<<(const std::string& rhs) {

    format.push_back(rhs);
    return *this;
}

std::vector<std::variant<std::string, logger_format::type>>::iterator logger_format::begin() {

    return format.begin();
} 

std::vector<std::variant<std::string, logger_format::type>>::iterator logger_format::end() {

    return format.end();
} 

logger_format operator<<(const std::string& lhs, const logger_format::type& rhs) {

    logger_format format;
    format << lhs << rhs;
    return format;
}

logger_format operator<<(const char* lhs, const logger_format::type& rhs) {

    return (std::string(lhs) << rhs);
}