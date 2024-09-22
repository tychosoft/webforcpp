// Copyright (C) 2024 Tycho Softworks.
// This code is licensed under MIT license.

#ifndef WEB_HTTP_HPP_
#define WEB_HTTP_HPP_

#define CPPHTTPLIB_USE_POLL
#if defined(_MSC_VER) || defined(__MINGW32__) || defined(__MINGW64__) || defined(WIN32)
#if _WIN32_WINNT < 0x0600 && !defined(_MSC_VER)
#undef  _WIN32_WINNT
#define _WIN32_WINNT    0x0600  // NOLINT
#endif
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#ifndef _WIN32
#define _WIN32
#endif
#endif

#include "httplib.h"

#include <exception>
#include <cstdint>
#include <memory>

namespace web::http {
using namespace httplib;

// Additional special functions and helpers...

#include "_client_helper.hpp"

}   // end namespace

#endif
