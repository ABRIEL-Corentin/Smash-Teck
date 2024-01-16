////////////////////////
//
//  Created on Tue Sep 26 2023
//
//  config.hpp
//
////////////////////////

#pragma once

#include "singleton.hpp"
#include <string>

namespace engine
{
    class Config : public Singleton<Config>
    {
        public:
            Config() = default;

            bool loadArgs(int argc, char **argv);
            size_t getPort();
            size_t getReceiverPort();
            std::string getReceiverIP();

        private:
            int m_port;
            std::string m_ip;
            int m_receiver_port;
            std::string m_receiver_ip;
    };
}
