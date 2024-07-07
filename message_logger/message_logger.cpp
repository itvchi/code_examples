#include "message_logger.h"
#include "message_logger_api.h"

#include <iostream>

#include <sys/stat.h>

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

void message_logger::log(const std::string& channel, const log_level level, const std::string& data) {

    if (level_per_channel.count(channel)) {
        if (level <= level_per_channel[channel]) {
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