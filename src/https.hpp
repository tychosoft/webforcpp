// Copyright (C) 2024 Tycho Softworks.
// This code is licensed under MIT license.

#ifndef WEB_HTTPS_HPP_
#define WEB_HTTPS_HPP_

#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "httplib.h"

#include <cstdint>
#include <memory>

namespace web::https {
using namespace httplib;

// Additional special functions we may add...

inline auto make_client(const std::string& uri) {
    return std::make_shared<Client>(uri);
}

inline auto make_client(const std::string& host, uint16_t port) {
    return std::make_shared<SSLClient>(host, port);
}
}   // end namespace

#endif
