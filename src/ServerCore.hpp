#ifndef SERVER_CORE_HPP
#define SERVER_CORE_HPP

#include <map>
#include <string>
#include <thread>
#include <SFML/Network.hpp>
#include "Core.hpp"

#define TCP_MAX_LENGTH 20000

class Player;

class ServerCore: public Core {
public:
    ServerCore(unsigned short port);
    virtual ~ServerCore();
    
    void startAcceptingNewPlayers();
    void stopAcceptingNewPlayers();
protected:
    virtual void update(float updateTime) override;
private:
    std::map<std::string, Player*> m_players;
    
    unsigned short m_port;
    bool m_isAcceptingNewPlayers;
    std::thread* m_newPlayersListenerThread;
    sf::TcpListener* m_tcpListener;
    void newPlayersListener();
    
    bool addPlayer(Player* player);
    void removePlayer(const std::string& name);
};

#endif