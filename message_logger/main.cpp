#include "message_logger_api.h"
#include <unistd.h>

#include <iostream>

int main(int argc, char const *argv[]) {

    MSG_INIT();

    MSG_IN() << "Test info level";
    MSG_DB() << "Test debug level";

    while (true) {
        sleep(2);
        MSG_IN() << "Test info level";
    }

    return 0;
}
