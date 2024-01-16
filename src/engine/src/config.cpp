////////////////////////
//
//  Created on Tue Oct 31 2023
//
//  config.cpp
//
////////////////////////

#include "config.hpp"

namespace engine
{
    bool Config::loadArgs(int argc, char **argv)
    {
        if (argc == 1)
            return false;
        if (argc != 4)
            return true;
        if (((m_port = std::stoi(argv[1])) < 0) || (m_port > 65535) || (m_port < 1024))
            return true;
        if (((m_receiver_port = std::stoi(argv[3])) < 0) ||
            (m_receiver_port > 65535) || (m_receiver_port < 1024))
            return true;
        m_receiver_ip = argv[2];
        return false;
    }

    size_t Config::getPort()
    {
        return m_port;
    }

    size_t Config::getReceiverPort()
    {
        return m_receiver_port;
    }

    std::string Config::getReceiverIP()
    {
        return m_receiver_ip;
    }
}
