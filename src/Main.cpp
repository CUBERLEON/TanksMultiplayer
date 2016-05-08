#include <iostream>
#include <chrono>
#include <thread>
#include <string>
#include <vector>
#include <cstdio>
#include <sstream>
#include "ServerCore.hpp"
#include "ClientCore.hpp"
#include "Renderer.hpp"
#include "sys/Debug.hpp"

void process_command(std::string text);

int main() {
    try {
        std::string text;
        while (true) {
            std::cout << ">";
            while (!std::getline(std::cin, text) || text == "");
            
            process_command(text);
            
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        exit(1);
    }    
    
    return 0; 
}

void process_command(std::string text) {
    try {
        std::stringstream s(text);
        std::string command, tmp;
        std::vector<std::string> args;
        
        s >> command;
        while (s >> tmp) args.push_back(tmp);
        
        if (command == "exit") {
            exit(0);
        } else if (command == "create") {
            Core* core = new ServerCore();
            core->getRenderer()->setSettings(2);
            core->getRenderer()->createWindow(900, 600, "Tanks - Host");
            core->start();
            delete core;
        } else if (command == "connect") {
            Core* core = new ClientCore();
            core->getRenderer()->setSettings(2);
            core->getRenderer()->createWindow(900, 600, "Tanks - Client");
            core->start();
            delete core;
        } else if (command == "help") {
            std::cout << "Help is currently not available!" << std::endl;
        } else {
            std::cout << "'" << command << "' is unknown command. Please type 'help' for usage instructions." << std::endl;
        }
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}