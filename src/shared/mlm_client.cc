#include "mlm_client.h"
#include <fty_common_mlm_pool.h>

class ClientHolder::Impl
{
public:
    Impl()
        : m_client(std::move(mlm_pool.get()))
    {
    }

    MlmClientPool::Ptr m_client;
};

ClientHolder::ClientHolder()
    : m_impl(new Impl)
{
}

ClientHolder::~ClientHolder()
{
}

zmsg_t* ClientHolder::recv(const std::string& uuid, uint32_t timeout)
{
    return m_impl->m_client->recv(uuid, timeout);
}

zmsg_t* ClientHolder::requestreply(
    const std::string& address, const std::string& subject, uint32_t timeout, zmsg_t** content_p)
{
    return m_impl->m_client->requestreply(address, subject, timeout, content_p);
}

int ClientHolder::sendto(const std::string& address, const std::string& subject, uint32_t timeout, zmsg_t** content_p)
{
    return m_impl->m_client->sendto(address, subject, timeout, content_p);
}

bool ClientHolder::connected()
{
    return m_impl->m_client->connected();
}

const char* ClientHolder::subject()
{
    return m_impl->m_client->subject();
}

const char* ClientHolder::sender()
{
    return m_impl->m_client->sender();
}

ClientHolder::operator bool() const
{
    return m_impl->m_client.getPointer() != nullptr;
}

ClientHolder getMlmClient()
{
    return ClientHolder();
}
