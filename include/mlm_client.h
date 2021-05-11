#pragma once
#include <fty_common_mlm_tntmlm.h>
#include <memory>

class ClientHolder
{
public:
    ClientHolder(const ClientHolder&) = delete;
    ClientHolder(ClientHolder&&)      = default;
    ClientHolder& operator=(const ClientHolder&) = delete;
    ClientHolder& operator=(ClientHolder&&) = default;
    ~ClientHolder();

    zmsg_t* recv(const std::string& uuid, uint32_t timeout);
    zmsg_t* requestreply(const std::string& address, const std::string& subject, uint32_t timeout, zmsg_t** content_p);
    int     sendto(const std::string& address, const std::string& subject, uint32_t timeout, zmsg_t** content_p);
    bool    connected();
    const char* subject();
    const char* sender();

    operator bool() const;

private:
    class Impl;
    std::unique_ptr<Impl> m_impl;

    ClientHolder();
    friend ClientHolder getMlmClient();
};

ClientHolder getMlmClient();
