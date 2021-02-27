#include "EventLoop.h"

// EventEngine
#include <EventEngine/Events.h>
#include <EventEngine/private/EventLoopPrivate.h>
#include <EventEngine/private/EventConverter.h>

EventLoop::EventLoop() : Object(),
    m_eventLoopPrivate(new EventLoopPrivate()),
    m_eventConverter(new EventConverter())
{
    m_eventLoopPrivate->setup(m_eventConverter.get());
    m_eventConverter->setup(this, m_eventLoopPrivate.get());
}

EventLoop* EventLoop::Instance()
{
    static thread_local EventLoop object;
    return &object;
}

int EventLoop::exec()
{
    return m_eventLoopPrivate->exec();
}

void EventLoop::quit()
{
    std::cout << "quit called " << this << std::endl;
    exit(0);
}

void EventLoop::exit(int exitCode)
{
    QuitEventLoop msg = { exitCode };

    m_eventConverter->send<QuitEventLoop>(this, msg);
}

template<>
inline void EventLoop::receive<QuitEventLoop>(const QuitEventLoop& msg)
{
    std::cout << "EventLoop receive QuitEventLoop" << std::endl;
    int exitCode = msg.exitCode;

    m_eventLoopPrivate->exit(exitCode);
}

template<>
inline void EventLoop::receive<ConnectionEvent>(const ConnectionEvent& msg)
{
    std::cout << "EventLoop receive ConnectionEvent" << std::endl;
}
