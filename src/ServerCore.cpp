#include "ServerCore.hpp"

#include "World.hpp"
#include "Map.hpp"
#include "Player.hpp"
#include "sys/Debug.hpp"

#include <json/json.hpp>
using json = nlohmann::json;

ServerCore::ServerCore(unsigned short port)
: m_port(port), m_isAcceptingNewPlayers(false), m_newPlayersListenerThread(nullptr), m_tcpListener(nullptr)
{
    startAcceptingNewPlayers();
    
    m_world = new World(new Map("default"));
    // Tank* t = new Tank(10, 5, new Polygon("tank_1"));
    // t->setPos({40, 40});
    // t->setRotDeg(15);
    // m_world->addTank(t);
}

ServerCore::~ServerCore()
{
    stopAcceptingNewPlayers();
    
    for (auto i = m_players.begin(); i != m_players.end();) {
        Player* tmp = i->second;
        i = m_players.erase(i);
        delete tmp;
    }
}

void ServerCore::startAcceptingNewPlayers() {
    if (m_isAcceptingNewPlayers)
        return;
    
    m_tcpListener = new sf::TcpListener;
   if (m_tcpListener->listen(m_port) != sf::Socket::Done) {
        throw std::runtime_error("Cannot listen to port " + std::to_string(m_port));
        exit(1);
    }
    m_newPlayersListenerThread = new std::thread(&ServerCore::newPlayersListener, this);
}

void ServerCore::stopAcceptingNewPlayers() {
    if (!m_isAcceptingNewPlayers)
        return;
    
    m_isAcceptingNewPlayers = false;
    m_newPlayersListenerThread->join();
    delete m_newPlayersListenerThread;
    delete m_tcpListener;
    m_newPlayersListenerThread = nullptr;
    m_tcpListener = nullptr;
}

void ServerCore::update(float updateTime) {
    //removes disconnected players
    for (auto i = m_players.begin(); i != m_players.end(); ++i)
        if (!i->second->isConnected()) {
            i = m_players.erase(i);
        }
        
    // Debug::info(std::to_string(m_players.size()));
       
    //syncs
    for (auto i = m_players.begin(); i != m_players.end(); ++i)
        i->second->sync(m_world);
    
    //updates world
    // for (unsigned int i = 0; i < m_players.size(); ++i) {
    //     if (m_players[i]->getInput()->getKeyboardKeyState(Input::Keyboard::A))
    //         m_players[i]->getTank()->rotate(updateTime);
    // }
}

void ServerCore::newPlayersListener() {
    m_isAcceptingNewPlayers = true;
    while (m_isAcceptingNewPlayers) {
        try {
            sf::TcpSocket* socket = new sf::TcpSocket;
            if (m_tcpListener->accept(*socket) != sf::Socket::Done) {
                delete socket;
                throw std::runtime_error("Couldn't accept TCP socket of player");
            }
            
            char data[TCP_MAX_LENGTH];
            std::size_t received;
            if (socket->receive(data, TCP_MAX_LENGTH, received) != sf::Socket::Done) {
                delete socket;
                throw std::runtime_error("Couldn't receive player's info");    
            }
            
            json playerInfo = json::parse(data);
            if (playerInfo["type"] != "connection")
                throw std::runtime_error("Incorrect msg type");
            Player* player = new Player(playerInfo["name"], socket);
            
            if (!addPlayer(player))
                delete player;
        } catch (const std::exception& r) {
            Debug::error(r.what());
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

bool ServerCore::addPlayer(Player* player) {
    if (!m_players.count(player->getName())) {
        if (player->send({{"type", "connection"}, {"status", 1}, {"msg", "Success"}})) {
            m_players[player->getName()] = player;
            return true;
        }
    } else
        player->send({{"type", "connection"}, {"status", 0}, {"msg", "Player with such name already exists"}});
    return false;
}

void ServerCore::removePlayer(const std::string& name) {
    m_players.erase(m_players.find(name));
}