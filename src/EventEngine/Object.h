#ifndef EVENTENGINE_OBJECT_H
#define EVENTENGINE_OBJECT_H

// Nod
#include <nod/nod.hpp>

class EventLoop;

class Object
{

public:
    Object();
    virtual ~Object();

public:
    nod::signal<void()>* destroySignal() { return &m_destroySignal; }

public:
    EventLoop* eventLoop() const;

private:
    nod::signal<void()> m_destroySignal;

};

#endif // EVENTENGINE_OBJECT_H
