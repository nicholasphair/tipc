#ifndef TIPC_UNIFICATIONERROR_HPP
#define TIPC_UNIFICATIONERROR_HPP

#include <exception>
#include <string>

class UnificationError: public std::exception {
public:
    UnificationError(const char * msg);
    virtual const char* what() const throw() override;
private:
    const char * msg;
};


#endif //TIPC_UNIFICATIONERROR_HPP
