#ifndef _MESSAGE_LOGGER_API_H_
#define _MESSAGE_LOGGER_API_H_

#include <string>
#include <sstream>
#include <map>
#include <fstream>

#include "message_logger.h"

#include "logger_format.h"

class message_logger {
    public:
        message_logger();
        ~message_logger();

        void register_channel(const std::string name, const log_level level);
        void set_format(const logger_format format);

        void log(const std::string& channel, const log_level level, const std::string& data);
        
    private:
        std::fstream config;
        std::map<std::string, log_level> level_per_channel;
        logger_format message_format;
};

class message_logger_stream {
    public:
        message_logger_stream(message_logger& logger, const std::string& channel, const log_level level);
        message_logger_stream& operator<<(const std::string_view data);
        ~message_logger_stream();

    private:
        message_logger& ml;
        std::string m_channel;
        log_level m_level;
        std::stringstream data_stream;
};

void init_logger();
message_logger& get_logger();

#define DBG

#ifdef DBG
#define MSG_INIT()      init_logger()
#define MSG_NO()        message_logger_stream(get_logger(), "default_channel", log_level::NOTICE)
#define MSG_IN()        message_logger_stream(get_logger(), "default_channel", log_level::INFO)
#define MSG_DB()        message_logger_stream(get_logger(), "default_channel", log_level::DEBUG)
#else
#define MSG_INIT()      
#define MSG_NO()         
#define MSG_IN()         
#define MSG_DB()         
#endif

//std::ostream& operator<< (std::ostream& os, const log_level level);

#endif /* _MESSAGE_LOGGER_API_H_ */