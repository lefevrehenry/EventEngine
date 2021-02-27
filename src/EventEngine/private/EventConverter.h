#ifndef EVENTENGINE_EVENTCONVERTER_H
#define EVENTENGINE_EVENTCONVERTER_H

// EventEngine
#include <EventEngine/EventLoop.h>
#include <EventEngine/private/EventLoopPrivate.h>
#include <EventEngine/private/EventRegistry.h>

// ZMQPP
#include <zmqpp/zmqpp.hpp>

// Standard Library
#include <type_traits>

class EventLoop;
class EventLoopPrivate;

class EventConverter
{
    using Executor = void(EventConverter::*)(zmqpp::message&);
    using EventsMapper = std::map<EventId, Executor>;

    template< typename T >
    using IsPod = std::enable_if<std::is_pod<T>::value, bool>;

public:
    EventConverter();

public:
    void setup(EventLoop* eventLoop, EventLoopPrivate* eventLoopPrivate);

private:
    template< typename T >
    void registerEvent();

    template< typename T, typename IsPod<T>::type = true >
    void Serialize(T& msg, zmqpp::message& message)
    {
        message.add_raw<T>(&msg, sizeof(T));
    }

    template< typename T, typename IsPod<T>::type = true >
    void Deserialize(T& msg, zmqpp::message& message)
    {
        const T* t;

        message >> t;

        msg = *t;
    }

public:
    template< typename T >
    void send(EventLoop* eventLoop, T& msg)
    {
        if(!eventLoop)
            return;

        EventLoopPrivate* eventLoopPrivate = eventLoop->eventLoopPrivate();

        if(!eventLoopPrivate)
            return;

        EventId id = EventRegistry::Id<T>();

        zmqpp::message message;
        message << id;

        {
            Serialize<T>(msg, message);
        }

        m_eventLoopPrivate->send(eventLoopPrivate, message);
    }

    void receive(zmqpp::message& message)
    {
        EventId id;
        message >> id;

        if(m_eventsMapper.find(id) != m_eventsMapper.end())
        {
            const Executor& executor = m_eventsMapper[id];

            if(!executor)
                return (this->*executor)(message);
        }

        throw std::runtime_error("Unknow EventId");
    }

private:
    template< typename T >
    void executor(zmqpp::message& message);

private:
    EventLoop* m_eventLoop;
    EventLoopPrivate* m_eventLoopPrivate;

    EventsMapper m_eventsMapper;

};

#endif // EVENTENGINE_EVENTCONVERTER_H
