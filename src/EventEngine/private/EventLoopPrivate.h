#ifndef EVENTENGINE_EVENTLOOPPRIVATE_H
#define EVENTENGINE_EVENTLOOPPRIVATE_H

// ZMQPP
#include <zmqpp/zmqpp.hpp>

// Standard Library
#include <string>

class EventConverter;

class EventLoopPrivate
{

public:
    EventLoopPrivate();

public:
    void setup(EventConverter* eventConverter);

private:
    const std::string& identifier() const;

private:
    void initialize();
    void finalize();
    int run();

public:
    int exec();

    void quit();
    void exit(int exitCode);

public:
    void send(EventLoopPrivate* eventLoopPrivate, zmqpp::message& message);

private:
    void process(zmqpp::message& message) const;

private:
    zmqpp::poller m_poller;
    zmqpp::socket* m_socket;

    std::string m_identifier;
    bool m_running;
    int m_exitCode;

    EventConverter* m_eventConverter;

};

#endif // EVENTENGINE_EVENTLOOPPRIVATE_H
