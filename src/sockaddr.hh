// SPDX-License-Identifier: LGPL-3.0-only
#ifndef IP2UNIX_SOCKETADDR_HH
#define IP2UNIX_SOCKETADDR_HH
#include <variant>

#include <netinet/in.h>

struct SockAddr : public sockaddr_storage
{
    SockAddr();
    SockAddr(const sockaddr*);

    static std::optional<SockAddr> create(const std::string&, uint16_t,
                                          sa_family_t = AF_INET);

    std::optional<std::string> get_host(void) const;
    bool set_host(const std::string&);

    std::optional<uint16_t> get_port(void) const;
    bool set_port(uint16_t);

    void apply_addr(struct sockaddr*, socklen_t*) const;

    inline std::optional<std::string> get_port_str(void) const {
        auto port = this->get_port();
        if (port)
            return std::to_string(port.value());
        return std::nullopt;
    };
};

#endif
