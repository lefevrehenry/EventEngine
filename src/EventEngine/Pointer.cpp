#include "Pointer.h"

// EventEngine
#include <EventEngine/EventLoop.h>

Pointer::Pointer(Object* object) : Object(),
    m_object(nullptr),
    m_connection()
{
    reset(object);
}

Pointer::Pointer(const Pointer &other) :
    m_object(nullptr),
    m_connection()
{
    reset(other.m_object);
}

Pointer::Pointer(Pointer &&other) :
    m_object(nullptr),
    m_connection()
{
    m_connection = std::move(other.m_connection);   // move connection first
    m_object = std::move(other.m_object);
}

Pointer::~Pointer()
{
    m_connection.disconnect();
}

Object* Pointer::get() const
{
    return m_object;
}

void Pointer::reset()
{
    reset(nullptr);
}

void Pointer::reset(Object* object)
{
    m_connection.disconnect();

    m_object = object;

    if(object)
        m_connection = EventLoop::Connect(object->destroySignal(), this, &Pointer::reset);
}
