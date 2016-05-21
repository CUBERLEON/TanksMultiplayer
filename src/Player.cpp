#include "Player.hpp"

#include "Input.hpp"
#include "World.hpp"
#include "sys/Debug.hpp"

Player::Player(const std::string& name, sf::TcpSocket* socket)
: m_name(name), m_input(new Input()), m_ip(socket->getRemoteAddress().toString()), m_port(socket->getRemotePort()), m_tcpSocket(socket), m_udpSocket(new sf::UdpSocket()), m_isConnected(true)
{
    m_udpSocket->bind(socket->getLocalPort());
}

Player::~Player()
{
    delete m_input;
    delete m_tcpSocket;
    delete m_udpSocket;
}

Input* Player::getInput() const {
    return m_input;
}

void Player::sync(const World* world) {
    // json 
    // if (receive())
}

bool Player::send(const json& r) {
    std::string data = r.dump();
    if (data.size() + 1 > TCP_MAX_LENGTH)
        return false;
    sf::Socket::Status res = m_tcpSocket->send(data.c_str(), data.size() + 1);
    
    if (res == sf::Socket::Disconnected)
        m_isConnected = false;
        
    return res == sf::Socket::Done;
}

bool Player::receive(json& r) {
    sf::Socket::Status res;
    try {
        char data[TCP_MAX_LENGTH];
        std::size_t received;
        res = m_tcpSocket->receive(data, TCP_MAX_LENGTH, received);
        
        if (res == sf::Socket::Disconnected)
            m_isConnected = false;
        if (res == sf::Socket::Done)
            r = json::parse(data);
    } catch (const std::exception& e) {
        Debug::error(e.what());
        return false;
    }
    return res == sf::Socket::Done;
}

bool Player::udpSend(const json& r) {
    std::string data = r.dump();
    if (data.size() + 1 > sf::UdpSocket::MaxDatagramSize)
        return false;
    sf::Socket::Status res = m_udpSocket->send(data.c_str(), data.size() + 1, sf::IpAddress(m_ip), m_port);
    
    if (res == sf::Socket::Disconnected)
        m_isConnected = false;
        
    return res == sf::Socket::Done;
}

bool Player::udpReceive(json& r) {
    sf::Socket::Status res;
    try {
        char data[sf::UdpSocket::MaxDatagramSize];
        std::size_t received;
        sf::IpAddress sender;
        unsigned short port;
        res = m_udpSocket->receive(data, sf::UdpSocket::MaxDatagramSize, received, sender, port);
        
        if (sender.toString() != m_ip || port != m_port)
            return false;
        
        if (res == sf::Socket::Disconnected)
            m_isConnected = false;
        if (res == sf::Socket::Done)
            r = json::parse(data);
    } catch (const std::exception& e) {
        Debug::error(e.what());
        return false;
    }
    return res == sf::Socket::Done;
}