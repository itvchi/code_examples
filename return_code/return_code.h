#ifndef _RETURN_CODE_H_
#define _RETURN_CODE_H_

#include <set>
#include <ostream>

class return_code {
    public:
        enum error_code {
            Ok,
            Error,

            ErrorIO,
            ErrorTimeout,
            ErrorNullptr
        };

        return_code() = default;
        return_code(const return_code& rc);
        return_code(const error_code ec);

        bool operator==(const return_code& rc);
        bool operator!=(const return_code& rc);
        bool operator==(const error_code ec);
        bool operator!=(const error_code ec);
        operator bool();

        friend std::ostream& operator<<(std::ostream& lhs, const return_code& rhs);

    private:
        std::set<error_code> error_codes;
};

#endif /* _RETURN_CODE_H_ */