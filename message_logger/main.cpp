#include "liblogger/message_logger_api.h"
#include <unistd.h>

#include <iostream>

int main(int argc, char const *argv[]) {

    MSG_INIT();

    get_logger().set_format("[" << logger_format::DateTime << "] [" << logger_format::LevelColor << "] [" << logger_format::Channel << "] ");

    MSG_IN() << "Test info level";
    MSG_DB() << "Test debug level";

    while (true) {
        sleep(2);
        MSG_IN() << "Test info level";
        sleep(1);
        MSG_NO() << "Test notice level";
    }

    return 0;
}
