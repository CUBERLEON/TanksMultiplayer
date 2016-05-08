#ifndef SERVER_CORE_HPP
#define SERVER_CORE_HPP

#include "Core.hpp"

class ServerCore: public Core {
public:
    ServerCore();
    ~ServerCore();
    
    void sync() override;
protected:
private:
};

#endif