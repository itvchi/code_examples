#include "message_logger.h"
#include "message_logger_api.h"

#include <iostream>

#include <sys/stat.h>

static std::map<log_level, std::string> level_map = {
    {log_level::EMERG,      "EMERG"     },
    {log_level::ALERT,      "ALERT"     },
    {log_level::CRIT,       "CRIT"      },
    {log_level::ERR,        "ERR"       },
    {log_level::WARNING,    "WARNING"   },
    {log_level::NOTICE,     "NOTICE"    },
    {log_level::INFO,       "INFO"      },
    {log_level::DEBUG,      "DEBUG"     },
    {log_level::NOISE,      "NOISE"     },
    {log_level::RACKET,     "RACKET"    },
    {log_level::TRACE,      "TRACE"     },
};
 
std::ostream& operator<< (std::ostream& os, const log_level level) {
    
    if (level_map.count(level)) {
        os << level_map[level];
    }

    return os;
}

message_channel::message_channel(const std::string& _name, const log_level _level) : name{_name}, level{_level} {

}

message_logger::message_logger() {

    // std::remove("./config");

    // if (mkfifo("./config", 0666) == -1) {
    //     perror("mkfifo");
    //     exit(EXIT_FAILURE);
    // }
}

message_logger::~message_logger() {

    // config.close();
    // std::remove("./config");
}

void message_logger::register_channel(const std::string name, const log_level level) {

    level_per_channel[name] = level;

    // std::ofstream config("./config", std::fstream::out | std::fstream::trunc);
    // if (config.is_open()) {
    //     for (const auto& [channel, level] : level_per_channel) {
    //         config << channel << ":" << static_cast<unsigned int>(level) << "\n";
    //     }
    //     config.close();
    // }
}

void message_logger::set_format(const logger_format format) {
    message_format = format;
}

#define COLOR_RESET     "\x1b[0m"
#define COLOR_BLACK     "\x1b[30m"
#define COLOR_RED       "\x1b[31m"
#define COLOR_GREEN     "\x1b[32m"
#define COLOR_YELLOW    "\x1b[33m"    
#define COLOR_BLUE      "\x1b[34m"
#define COLOR_MAGENTA   "\x1b[35m"    
#define COLOR_CYAN      "\x1b[36m"
#define COLOR_WHITE     "\x1b[37m"

static std::string level_color(const log_level level) {

    std::stringstream fmt_ss;

    switch (level) {
        case log_level::EMERG:
            fmt_ss << COLOR_RED << level << COLOR_RESET;
            break;
        case log_level::ALERT:
            fmt_ss << COLOR_RED << level << COLOR_RESET;
            break;
        case log_level::CRIT:
            fmt_ss << COLOR_RED << level << COLOR_RESET;
            break;
        case log_level::ERR:
            fmt_ss << COLOR_RED << level << COLOR_RESET;
            break;
        case log_level::WARNING:
            fmt_ss << COLOR_YELLOW << level << COLOR_RESET;
            break;
        case log_level::NOTICE:
            fmt_ss << COLOR_CYAN << level << COLOR_RESET;
            break;
        case log_level::INFO:
            fmt_ss << COLOR_WHITE << level << COLOR_RESET;
            break;
        case log_level::DEBUG:
            fmt_ss << COLOR_BLUE << level << COLOR_RESET;
            break;
        case log_level::NOISE:
            fmt_ss << COLOR_BLUE << level << COLOR_RESET;
            break;
        case log_level::RACKET:
            fmt_ss << COLOR_BLUE << level << COLOR_RESET;
            break;
        case log_level::TRACE:
            fmt_ss << COLOR_BLUE << level << COLOR_RESET;
            break;
        default:
            break;
    }

    return fmt_ss.str();
}

void message_logger::log(const std::string& channel, const log_level level, const std::string& data) {

    if (level_per_channel.count(channel)) {
        if (level <= level_per_channel[channel]) {
            /* Print format */
            for (const auto& element : message_format) {

            }
            /* then print message */
            std::cout << data;
        }
    }
}

message_logger_stream::message_logger_stream(message_logger& logger, const std::string& channel, const log_level level) :
    ml{logger}, m_channel(channel), m_level(level) {

}

message_logger_stream& message_logger_stream::operator<<(const std::string_view data) {

    data_stream << data;
    return *this;
}

message_logger_stream::~message_logger_stream() {

    data_stream << std::endl;
    ml.log(m_channel, m_level, data_stream.str());
}

message_logger* ml_ptr = nullptr;

void init_logger() {
    
    if (ml_ptr == nullptr) {
        ml_ptr = new message_logger();
        ml_ptr->register_channel("default_channel", log_level::INFO);
    }

}

message_logger& get_logger() {

    return *ml_ptr;
}