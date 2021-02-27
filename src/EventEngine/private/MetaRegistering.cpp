#include "MetaRegistering.h"

MetaRegistering::MetaRegistering(const std::string& identifier, const std::weak_ptr<zmqpp::socket>& socket) :
    m_identifier(identifier),
    m_socket(socket)
{
}

zmqpp::socket* MetaRegistering::socket() const
{
    std::shared_ptr<zmqpp::socket> socket(m_socket);

    if(!socket)
        return nullptr;

    return socket.get();
}
