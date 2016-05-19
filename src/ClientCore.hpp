#ifndef CLIENT_CORE_HPP
#define CLIENT_CORE_HPP

#include "Core.hpp"

class ClientCore: public Core {
public:
    ClientCore();
    ~ClientCore();
    
    virtual void sync() override;
protected:
private:
};

#endif