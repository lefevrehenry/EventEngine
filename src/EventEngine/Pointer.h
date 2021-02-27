#ifndef EVENTENGINE_POINTER_H
#define EVENTENGINE_POINTER_H

// EventEngine
#include <EventEngine/Object.h>

// Nod
#include <nod/nod.hpp>

class Pointer : public Object
{

public:
    // default ctor
    explicit Pointer(Object* object = nullptr);
    // copy ctor
    Pointer(const Pointer& other);
    // move ctor
    Pointer(Pointer&& other);
    // dtor
    virtual ~Pointer();

public:
    Object* get() const;

    void reset();
    void reset(Object* object);

public:
    explicit operator bool() const {
        return get() != nullptr;
    }
    Pointer& operator=(const Pointer& other)
    {
        reset(other.m_object);
        return *this;
    }
    bool operator==(const Pointer& other) const {
        return get() == other.get();
    }
    bool operator!=(const Pointer& other) const {
        return get() != other.get();
    }
    Object& operator*() const {
        return *get();
    }
    Object* operator->() const {
        return get();
    }

private:
    Object* m_object;
    nod::connection m_connection;

};

#endif // EVENTENGINE_POINTER_H
