#ifndef _MESSAGE_LOGGER_H_
#define _MESSAGE_LOGGER_H_

#include <string>
#include <vector>

enum class log_level {
    EMERG = 0,
    ALERT,
    CRIT,
    ERR,
    WARNING,
    NOTICE,
    INFO,
    DEBUG,
    NOISE,
    RACKET,
    TRACE
};

class message_channel {
    public:
        message_channel(const std::string& _name, const log_level _level);

    private:
        std::string name;
        log_level level;
};

#endif /* _MESSAGE_LOGGER_H_ */