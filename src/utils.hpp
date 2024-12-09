// Copyright (C) 2024 Tycho Softworks.
// This code is licensed under MIT license.

#ifndef WEB_UTILITY_HPP_
#define WEB_UTILITY_HPP_

#include <string>
#include <cstdint>
#include <cstring>

#if defined(_MSC_VER) || defined(__MINGW32__) || defined(__MINGW64__) || defined(WIN32)
#if _WIN32_WINNT < 0x0600 && !defined(_MSC_VER)
#undef  _WIN32_WINNT
#define _WIN32_WINNT    0x0600  // NOLINT
#endif
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#else
#include <sys/socket.h>
#include <net/if.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <ifaddrs.h>
#endif

namespace web {
class net_address {
public:
    static inline const socklen_t maxsize = sizeof(struct sockaddr_storage);

    net_address() noexcept = default;

    explicit net_address(int family = AF_UNSPEC, uint16_t value = 0) noexcept {
        switch(family) {
        case AF_INET:
            memset(&(reinterpret_cast<struct sockaddr_in*>(&store_))->sin_addr.s_addr, 0, 4);
            (reinterpret_cast<struct sockaddr_in *>(&store_))->sin_port = htons(value);
            break;
        case AF_INET6:
            memset(&(reinterpret_cast<struct sockaddr_in6*>(&store_))->sin6_addr.s6_addr, 0, 16);
             (reinterpret_cast<struct sockaddr_in6 *>(&store_))->sin6_port = htons(value);
            break;
        default:
            break;
        }
    }

    explicit net_address(const std::string& addr, uint16_t value = 0) noexcept {
        set(addr, value);
    }

    net_address(const net_address& from) = default;
    auto operator=(const net_address& from) -> net_address& = default;

    operator bool() const noexcept {
        return store_.ss_family != AF_UNSPEC;
    }

    operator std::string() const noexcept {
        return host();
    }

    operator uint16_t() const noexcept {
        return port();
    }

    auto operator!() const noexcept {
        return store_.ss_family == AF_UNSPEC;
    }

    auto operator*() const noexcept {
        return host();
    }

    void clear() {
        store_.ss_family = AF_UNSPEC;
    }

    void port_if(uint16_t value) {
        if(!port())
            port(value);
    }

    void port(uint16_t value) {
        switch(store_.ss_family) {
        case AF_INET:
            (reinterpret_cast<struct sockaddr_in *>(&store_))->sin_port = htons(value);
            break;
        case AF_INET6:
             (reinterpret_cast<struct sockaddr_in6 *>(&store_))->sin6_port = htons(value);
            break;
        default:
            break;
        }
    }

    auto port() const noexcept -> uint16_t {
        switch(store_.ss_family) {
        case AF_INET:
            return ntohs((reinterpret_cast<const struct sockaddr_in *>(&store_))->sin_port);
        case AF_INET6:
            return ntohs((reinterpret_cast<const struct sockaddr_in6 *>(&store_))->sin6_port);
        default:
            return 0;
        }
    }

    auto empty() const noexcept {
        return store_.ss_family == AF_UNSPEC;
    }

    void set(const std::string& str, uint16_t in_port = 0) noexcept {
        store_.ss_family = AF_UNSPEC;
        auto cp = str.c_str();
        if(str == "*")
            cp = "0.0.0.0";
        else if(str == "[*]" || str == "::*")
            cp = "::";
        if(strchr(cp, ':') != nullptr) {
            auto ipv6 = reinterpret_cast<struct sockaddr_in6*>(&store_);
            if(inet_pton(AF_INET6, cp, &(ipv6->sin6_addr)) > 0) {
                ipv6->sin6_family = AF_INET6;
                ipv6->sin6_port = htons(in_port);
                return;
            }
        } else if(strchr(cp, '.') != nullptr) {
            auto ipv4 = reinterpret_cast<struct sockaddr_in*>(&store_);
            if(inet_pton(AF_INET, cp, &(ipv4->sin_addr)) > 0) {
                ipv4->sin_family = AF_INET;
                ipv4->sin_port = htons(in_port);
                return;
            }
        }
    }

    auto host() const -> std::string {
        char buf[256];
        const struct sockaddr_in *ipv4{nullptr};
        const struct sockaddr_in6 *ipv6{nullptr};
        switch(store_.ss_family) {
        case AF_INET:
            ipv4 = reinterpret_cast<const struct sockaddr_in*>(&store_);
            if(::inet_ntop(AF_INET, &(ipv4->sin_addr), buf, sizeof(buf)))
                return {buf};
            break;
        case AF_INET6:
            ipv6 = reinterpret_cast<const struct sockaddr_in6*>(&store_);
            if(::inet_ntop(AF_INET, &(ipv6->sin6_addr), buf, sizeof(buf)))
                return {buf};
            break;
        default:
            break;
        }
        return {};
    }

    static auto find(const std::string& host, const std::string& svc = "0", int family = AF_UNSPEC) {
        uint16_t value = 0;
        try {
            value = std::stoi(svc);
        } catch(...) {
            value = 0;
        }
        net_address address(host);
        if(!address.empty()) {
            address.port(value);
            return address;
        }
        const char *service = svc.c_str();
        if(svc.empty() || svc == "0")
            service = nullptr;

        struct addrinfo hints{};
        memset(&hints, 0, sizeof(struct addrinfo));
        hints.ai_family = family;
        if(value > 0)
            hints.ai_flags |= NI_NUMERICSERV;
        struct addrinfo *list{nullptr};
        auto result = getaddrinfo(host.c_str(), service, &hints, &list);
        if(list && !result)
            memcpy(&address.store_, list->ai_addr, list->ai_addrlen);
        if(list)
            freeaddrinfo(list);
        return address;
    }

protected:
    struct sockaddr_storage store_{AF_UNSPEC};
};
} // end namespace
#endif
