#include "ObjectRegistry.h"

// EventEngine
#include <EventEngine/Object.h>

ObjectRegistry::ObjectRegistry() :
    m_registry(new Registry<Object>())
{
}

ObjectRegistry* ObjectRegistry::Instance()
{
    static thread_local ObjectRegistry instance;
    return &instance;
}

void ObjectRegistry::addObject(Object* object)
{
    m_registry->addEntry(object);
}

void ObjectRegistry::removeObject(Object* object)
{
    m_registry->removeEntry(object);
}
