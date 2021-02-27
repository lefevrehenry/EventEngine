#ifndef EVENTENGINE_EVENTLOOP_H
#define EVENTENGINE_EVENTLOOP_H

// EventEngine
#include <EventEngine/Object.h>
#include <EventEngine/Events.h>

// Nod
#include <nod/nod.hpp>

// Standard Library
#include <memory>
#include <type_traits>
#include <iostream>

class EventLoopPrivate;
class EventConverter;

class EventLoop : public Object
{

private:
    EventLoop();

public:
    static EventLoop* Instance();

public:
    template< typename T, typename std::enable_if<std::is_base_of<Object,T>::value, bool>::type = true, class... Args >
    static nod::connection Connect(nod::signal<void(Args...)>* signal, T* target, void(T::*slot)(Args...))
    {
        nod::connection connection = signal->connect([target, slot](Args&&... args) {
            EventLoop* ev = EventLoop::Instance();

            // target lives under the same EventLoop (DirectConnetcion)
            if(ev == target->eventLoop())
                (target->*slot)(std::forward<Args>(args)...);
            else // (QueuedConnection)
            {
                //ev->callSlot(target, slot, std::forward<Args>(args)...);
            }
        });

        return connection;
    }

//    template< class... Args >
//    static void Connect(nod::signal<void(Args...)>* signal, Object* context, std::function<void(Args...)> function)
//    {
//    }

//    template< class... Args >
//    static void Connect(nod::signal<void(Args...)>* signal, Object* context, void(*function)(Args...))
//    {
//    }

//    static void Connect(nod::signal<void()>* signal, Object* context, std::function<void()> function)
//    {
//    }

public:
    int exec();

    void quit();
    void exit(int exitCode);

public:
//    void sendQuitEvent(EventLoop* eventLoop);
//    void receiveQuitEvent();

//    template< typename T >
//    void send(EventLoop* eventLoop, const T& msg)
//    {
//        m_eventConverter->send(eventLoop, msg);
//    }

    template< typename T >
    void receive(const T& msg)
    {
        throw std::runtime_error("Unknown message");
    }

public:
    EventLoopPrivate* eventLoopPrivate() const { return m_eventLoopPrivate.get(); }

private:
    std::unique_ptr<EventLoopPrivate> m_eventLoopPrivate;
    std::unique_ptr<EventConverter> m_eventConverter;

};

#endif // EVENTENGINE_EVENTLOOP_H
