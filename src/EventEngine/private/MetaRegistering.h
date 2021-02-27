#ifndef EVENTENGINE_METAREGISTERING_H
#define EVENTENGINE_METAREGISTERING_H

// ZMQPP
#include <zmqpp/zmqpp.hpp>

// Standard Library
#include <memory>
#include <string>

class MetaRegistering
{

public:
    MetaRegistering(const std::string& identifier, const std::weak_ptr<zmqpp::socket>& socket);

public:
    zmqpp::socket* socket() const;

private:
    std::string m_identifier;
    std::weak_ptr<zmqpp::socket> m_socket;

};

#endif // EVENTENGINE_METAREGISTERING_H
