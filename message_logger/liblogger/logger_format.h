#ifndef _LOGGER_FORMAT_H_
#define _LOGGER_FORMAT_H_

#include <string>
#include <variant>
#include <vector>

class logger_format {
    public:
        enum type {
            DateTime,
            Level,
            LevelColor,
            Channel
        };

        logger_format& operator<<(const logger_format& rhs);
        logger_format& operator<<(const type& rhs);
        logger_format& operator<<(const std::string& rhs);

        std::vector<std::variant<std::string, type>>::iterator begin();
        std::vector<std::variant<std::string, type>>::iterator end();

    private:
        std::vector<std::variant<std::string, type>> format;
};

logger_format operator<<(const std::string& lhs, const logger_format::type& rhs);
logger_format operator<<(const char* lhs, const logger_format::type& rhs);

#endif /* _LOGGER_FORMAT_H_ */