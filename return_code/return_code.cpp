#include "return_code.h"

return_code::return_code(const return_code& rc) {

    error_codes.insert(rc.error_codes.begin(), rc.error_codes.end());
}

return_code::return_code(const error_code ec) : error_codes{ec} {

}

/* Operators section */
bool return_code::operator==(const return_code& rc) {
            
    return (error_codes == rc.error_codes);
}

bool return_code::operator!=(const return_code& rc) {
            
    return !(*this == rc);
}

bool return_code::operator==(const error_code ec) {

    return ((error_codes.size() == 1) && (*error_codes.begin() == ec));
}

bool return_code::operator!=(const error_code ec) {

    return !(*this == ec);
}

return_code::operator bool() {

    return ((error_codes.size() == 1) && (*error_codes.begin() == return_code::Ok));
}

std::ostream& operator<<(std::ostream& lhs, const return_code& rhs) {

    if (rhs.error_codes.empty()) {
        lhs << "none";
    } else {
        auto error_code_it = rhs.error_codes.begin();
        const auto end_it = rhs.error_codes.end();
        while (error_code_it != end_it) {
            switch (*error_code_it) {
                case return_code::Ok: 
                    lhs << "ok";
                    break;
                case return_code::Error: 
                    lhs << "generic error";
                    break;
                case return_code::ErrorIO: 
                    lhs << "I/O error";
                    break;
                case return_code::ErrorTimeout: 
                    lhs << "timeout error";
                    break;
                case return_code::ErrorNullptr: 
                    lhs << "nullptr error";
                    break;
                default:
                    lhs << "unknown";
                    break;
            }

            if (++error_code_it != end_it) {
                lhs << ", ";
            }
        }
    }

    return lhs;
}