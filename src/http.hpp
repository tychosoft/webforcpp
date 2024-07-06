// Copyright (C) 2024 Tycho Softworks.
// This code is licensed under MIT license.

#ifndef WEB_HTTP_HPP_
#define WEB_HTTP_HPP_

#define CPPHTTPLIB_USE_POLL
#if defined(_MSC_VER) || defined(__MINGW32__) || defined(__MINGW64__) || defined(WIN32)
#if _WIN32_WINNT < 0x0600 && !defined(_MSC_VER)
#undef  _WIN32_WINNT
#define _WIN32_WINNT    0x0600
#endif
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

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
