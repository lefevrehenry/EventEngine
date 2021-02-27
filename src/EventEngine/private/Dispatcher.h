#ifndef EVENTENGINE_DISPATCHER_H
#define EVENTENGINE_DISPATCHER_H

// EventEngine
#include <EventEngine/private/MetaRegistering.h>

// ZMQPP
#include <zmqpp/zmqpp.hpp>

class Dispatcher
{

public:
    static MetaRegistering Register(const std::string& identifier);
    static void Deregister(const std::string& identifier);

public:
    static void Send(const std::string& identifier, zmqpp::message& message);

};

#endif // EVENTENGINE_DISPATCHER_H
