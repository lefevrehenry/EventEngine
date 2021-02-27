#include "EventLoopPrivate.h"

// EventEngine
#include <EventEngine/private/Dispatcher.h>
#include <EventEngine/private/MetaRegistering.h>
#include <EventEngine/private/EventConverter.h>

// Standard Library
#include <atomic>

// generate a unique identifier
static std::string GenerateIdentifier()
{

    // use to count each identifier generated
    static std::atomic_int N(0);

    return "event_loop_private_" + std::to_string(++N);
}

EventLoopPrivate::EventLoopPrivate() :
    m_poller(),
    m_socket(nullptr),
    m_identifier(GenerateIdentifier()),
    m_running(false),
    m_exitCode(0),
    m_eventConverter(nullptr)
{
}

void EventLoopPrivate::setup(EventConverter* eventConverter)
{
    m_eventConverter = eventConverter;
}

const std::string& EventLoopPrivate::identifier() const
{
    return m_identifier;
}

void EventLoopPrivate::initialize()
{
    MetaRegistering meta = Dispatcher::Register(m_identifier);

    m_socket = meta.socket();
    m_poller.add(*m_socket);
}

void EventLoopPrivate::finalize()
{
    Dispatcher::Deregister(m_identifier);
}

int EventLoopPrivate::run()
{
    m_running = true;

    while(m_running)
    {
        // if there is something to poll (blocking)
         if(m_poller.poll())
         {
             // if a message is received from the socket
             if(m_poller.has_input(*m_socket)) {
                 zmqpp::message input_message;

                // receive the message
                 m_socket->receive(input_message);

                 // process the message
                 process(input_message);
             }
         }
    }

    return m_exitCode;
}

int EventLoopPrivate::exec()
{
    if(m_running)
        throw std::runtime_error("EventLoop is already running");

    int exitCode = 0;

    initialize();

    {
        exitCode = run();
    }

    finalize();

    return exitCode;
}

void EventLoopPrivate::quit()
{
    exit(0);
}

void EventLoopPrivate::exit(int exitCode)
{
    m_running = false;
    m_exitCode = exitCode;
}

void EventLoopPrivate::send(EventLoopPrivate* eventLoopPrivate, zmqpp::message& message)
{
    if(!eventLoopPrivate)
        return;

    const std::string& identifier = eventLoopPrivate->identifier();

    if(m_identifier == identifier)
        process(message);
    else
       Dispatcher::Send(identifier, message);
}

void EventLoopPrivate::process(zmqpp::message& message) const
{
    m_eventConverter->receive(message);
}
