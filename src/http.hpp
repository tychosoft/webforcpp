// Copyright (C) 2024 Tycho Softworks.
// This code is licensed under MIT license.

#ifndef WEB_HTTP_HPP_
#define WEB_HTTP_HPP_

#include "httplib.h"

#include <cstdint>
#include <memory>

namespace web::http {
using namespace httplib;

// Additional special functions we may add...

inline auto make_client(const std::string& host, uint16_t port = 80) {
    return std::make_shared<Client>(host, port);
}
}   // end namespace

#endif
