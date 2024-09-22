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

// Additional special functions we may add...
using error = httplib::Error;
class bad_http final : public std::exception {
public:
    bad_http() = delete;
    bad_http(const bad_http& other) = default;
    explicit bad_http(error code, const char *msg) : err_(code), msg_(msg) {}
    auto operator=(const bad_http&) -> auto& = delete;

    auto err() const {
        return err_;
    }

    auto what() const noexcept -> const char * override {
        return msg_;
    }

private:
    error err_{error::Success};
    const char *msg_{nullptr};
};

inline auto get_client(std::shared_ptr<Client> ctx, const std::string& path) {
    auto result = ctx->Get(path);
    if(!result)
        throw bad_http(result.error(), "Internal failure");
    auto response = result.value();
    if(result.error() != error::Success)
        throw bad_http(result.error(), status_message(response.status));
    return response;
}

inline auto make_client(const std::string& host, uint16_t port = 80) {
    return std::make_shared<Client>(host, port);
}
}   // end namespace

#endif
