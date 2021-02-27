#include "EventConverter.h"

// EventEngine
#include <EventEngine/Events.h>

EventConverter::EventConverter() :
    m_eventLoop(nullptr),
    m_eventLoopPrivate(nullptr)
{
    registerEvent<ConnectionEvent>();
    registerEvent<QuitEventLoop>();
}

void EventConverter::setup(EventLoop* eventLoop, EventLoopPrivate* eventLoopPrivate)
{
    m_eventLoop = eventLoop;
    m_eventLoopPrivate = eventLoopPrivate;
}

template< typename T >
void EventConverter::registerEvent()
{
    EventId id = EventRegistry::Id<T>();
    m_eventsMapper[id] = &EventConverter::executor<T>;
}

template< typename T >
void EventConverter::executor(zmqpp::message& message)
{
    T msg;

    {
        Deserialize<T>(msg, message);
    }

    m_eventLoop->receive<T>(msg);
}
