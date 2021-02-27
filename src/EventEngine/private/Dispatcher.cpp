#include "Dispatcher.h"

// Standard Library
#include <map>
#include <memory>
#include <mutex>
#include <utility>

// make Dispatcher access thread-safe
static std::mutex mutex;

using Socket = std::shared_ptr<zmqpp::socket>;
using PairSockets = std::pair<Socket, Socket>;
using SocketMapper = std::map<std::string, PairSockets>;

static SocketMapper Registry;

// create one context for all EventLoop
static zmqpp::context& GetContext()
{
    static zmqpp::context Context;
    return Context;
}

static SocketMapper::iterator FindIdentifier(SocketMapper& registry, const SocketMapper::key_type& key)
{
    return registry.find(key);
}

MetaRegistering Dispatcher::Register(const std::string& identifier)
{
    std::lock_guard<std::mutex> guard(mutex);

    // check invalid identifier
    if(identifier == "")
        throw std::runtime_error("Register en EventLoopPrivate with a empty identifier");

    // found a matching entry
    SocketMapper::iterator it = FindIdentifier(Registry, identifier);

    // raise error if an entry is found
    if(it != Registry.end())
        throw std::runtime_error("Register an already registered EventLoopPrivate '" + identifier + "'");

    // create a new pair sockets associated with the entry
    //    * the 'server_socket' is the one used by the Dispatcher to speak with the client
    //    * the 'client_socket' is the one the client will listen to to receive message from the Dispatcher
    Socket server_socket = std::make_shared<zmqpp::socket>(GetContext(), zmqpp::socket_type::pair);
    Socket client_socket = std::make_shared<zmqpp::socket>(GetContext(), zmqpp::socket_type::pair);

    server_socket->bind("inproc://" + identifier);
    client_socket->connect("inproc://" + identifier);

    PairSockets sockets = {server_socket, client_socket};

    // add the entry in the registry
    Registry.insert({identifier, sockets});
    std::cout << "[REGISTRY]: register " << identifier << std::endl;

    return MetaRegistering(identifier, client_socket);
}

void Dispatcher::Deregister(const std::string& identifier)
{
    std::lock_guard<std::mutex> guard(mutex);

    // check invalid identifier
    if(identifier == "")
        throw std::runtime_error("Deregister en EventLoopPrivate with a empty identifier");

    // found a matching entry
    SocketMapper::iterator it = FindIdentifier(Registry, identifier);

    // no entry found, nothing happen
    if(it == Registry.end())
        return;

    std::cout << "[REGISTRY]: deregister " << identifier << std::endl;

    // remove the entry
    Registry.erase(it);
}

static Socket ServerSocket(const PairSockets& sockets)
{
    return sockets.first;
}

static Socket ClientSocket(const PairSockets& sockets)
{
    return sockets.second;
}

void Dispatcher::Send(const std::string& identifier, zmqpp::message& message)
{
    std::lock_guard<std::mutex> guard(mutex);

    // find a matching entry
    SocketMapper::iterator it = FindIdentifier(Registry, identifier);

    // raise error if no entry is found
    if(it == Registry.end())
        throw std::runtime_error("No EventLoopPrivate found with identifier '" + identifier + "'");

    const PairSockets& sockets = it->second;
    const Socket& socket = ServerSocket(sockets);

    socket->send(message);
}
