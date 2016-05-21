#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <SFML/Network.hpp>
#include <json/json.hpp>
using json = nlohmann::json;

#define TCP_MAX_LENGTH 20000

class Input;
class World;

class Player {
public:
    Player(const std::string& name, sf::TcpSocket* socket);
    ~Player();
    
    const std::string& getName() const { return m_name; }
    Input* getInput() const;
    
    const std::string& getIp() const { return m_ip; }
    unsigned short getPort() const { return m_port; }
    bool isConnected() const { return m_isConnected; }
    
    void sync(const World* world);
    
    bool send(const json& r);
    bool receive(json& r);
    bool udpSend(const json& r);
    bool udpReceive(json& r);
protected:
private:
    std::string m_name;
    Input* m_input;

    std::string m_ip;
    unsigned short m_port;
    
    sf::TcpSocket* m_tcpSocket;
    sf::UdpSocket* m_udpSocket;
    
    bool m_isConnected;
};

#endif