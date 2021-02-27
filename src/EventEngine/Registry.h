#ifndef EVENTENGINE_REGISTRY_H
#define EVENTENGINE_REGISTRY_H

// Standard Library
#include <vector>
#include <algorithm>
#include <memory>

template< typename T >
class RegistryListener
{
public:
    virtual void entryAdded(T* entry) {}
    virtual void entryRemoved(T* entry) {}
};

template< typename T >
class Registry
{
    using Iterator = typename std::vector<T*>::iterator;
    using Listener = std::shared_ptr<RegistryListener<T>>;

public:
    Registry() :
        m_entries(),
        m_listeners()
    {
    }

public:
    void entryAdded(T* entry)
    {
        for (Listener& listener : m_listeners)
            listener->entryAdded(entry);
    }
    void addEntry(T* entry)
    {
        Iterator it = std::find(m_entries.begin(), m_entries.end(), entry);

        if (it != m_entries.end())
            return;

        m_entries.push_back(entry);

        entryAdded(entry);
    }
    void entryRemoved(T* entry)
    {
        for (Listener& listener : m_listeners)
            listener->entryRemoved(entry);
    }
    void removeEntry(T* entry)
    {
        Iterator it = std::find(m_entries.begin(), m_entries.end(), entry);

        if (it != m_entries.end())
        {
            m_entries.erase(it);

            entryRemoved(entry);
        }
    }

private:
    std::vector<T*> m_entries;
    std::vector<Listener> m_listeners;

};

#endif // EVENTENGINE_REGISTRY_H
