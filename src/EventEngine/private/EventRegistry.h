#ifndef EVENTENGINE_EVENTREGISTRY_H
#define EVENTENGINE_EVENTREGISTRY_H

using EventId = unsigned int;

class EventRegistry
{

public:
    template< typename T >
    static EventId Id()
    {
        static thread_local EventId id = ++N;
        return id;
    }

private:
    static thread_local EventId N;

};

#endif // EVENTENGINE_EVENTREGISTRY_H
