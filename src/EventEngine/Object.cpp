#include "Object.h"

// EventEngine
#include <EventEngine/EventLoop.h>
#include <EventEngine/ObjectRegistry.h>

Object::Object() :
    m_destroySignal()
{
    ObjectRegistry::Instance()->addObject(this);
}

Object::~Object()
{
    ObjectRegistry::Instance()->removeObject(this);

    m_destroySignal();
}

EventLoop* Object::eventLoop() const
{
    return EventLoop::Instance();
}
