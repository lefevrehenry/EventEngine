#ifndef EVENTENGINE_OBJECTREGISTRY_H
#define EVENTENGINE_OBJECTREGISTRY_H

// EventEngine
#include <EventEngine/Registry.h>

// Standard Library
#include <memory>

class Object;

class ObjectRegistry
{

private:
    ObjectRegistry();

public:
    static ObjectRegistry* Instance();

// public:
//     Registry<Object>* registry() const
//     {
//         return m_registry.get();
//     }

public:
    void addObject(Object* object);
    void removeObject(Object* object);

private:
    std::shared_ptr<Registry<Object>> m_registry;

};

#endif // EVENTENGINE_OBJECTREGISTRY_H
