// Copyright (C) 2024 Tycho Softworks.
// This code is licensed under MIT license.

#ifndef WEB_HTTPS_HPP_
#define WEB_HTTPS_HPP_

#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "httplib.h"

#include <memory>

namespace web::https {
using namespace httplib;

// Additional special functions we may add...

inline auto make_client(const std::string& url) {
    return std::make_shared<SSLClient>(url);
}
}   // end namespace

#endif
