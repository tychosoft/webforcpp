// Copyright (C) 2024 Tycho Softworks.
// This code is licensed under MIT license.

#ifndef WEB_HTTPS_HPP_
#define WEB_HTTPS_HPP_

#include "httplib.h"

#include <memory>

namespace web::http {
using namespace httplib;

// Additional special functions we may add...

inline auto make_client(const std::string& url) {
    return std::make_shared<Client>(url);
}
}   // end namespace

#endif
