#include <iostream>
#include <thread>

#include <EventEngine/EventLoop.h>
#include <EventEngine/Object.h>
#include <EventEngine/Pointer.h>

// Nod
#include <nod/nod.hpp>

void server(EventLoop* ev)
{
    nod::signal<void()> signal;

    std::cout << "server ev: " << EventLoop::Instance() << std::endl;

    EventLoop::Connect(&signal, ev, &EventLoop::quit);

    std::cout << "[SERVER]: goes to sleep (4s)" << std::endl;

    std::this_thread::sleep_for(std::chrono::milliseconds(4000));

    // emit the signal
    signal();

    std::cout << "[SERVER]: job's done" << std::endl;
}

int main()
{
    std::cout << "hello" << std::endl;

    EventLoop* event_loop = EventLoop::Instance();

    std::cout << "Main ev: " << event_loop << std::endl;

    Object o;

//    {
//        Object o1;
//        Object o2;
//    }

    std::thread t1(server, event_loop);

//    std::cout << "[MAIN]: exec" << std::endl;
    int exitCode = event_loop->exec();

    t1.join();

    return exitCode;
}
