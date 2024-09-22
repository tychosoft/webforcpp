// Copyright (C) 2024 Tycho Softworks.
// This code is licensed under MIT license.

#ifndef WEB_HTTPS_HPP_
#define WEB_HTTPS_HPP_

#define CPPHTTPLIB_USE_POLL
#define CPPHTTPLIB_OPENSSL_SUPPORT
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

#include <cstdint>
#include <memory>

namespace web::https {
using namespace httplib;

// Additional special functions we may add...

using error = httplib::Error;
class bad_https final : public std::exception {
public:
    bad_https() = delete;
    bad_https(const bad_https& other) = default;
    explicit bad_https(error code, const char *msg) : err_(code), msg_(msg) {}
    auto operator=(const bad_https&) -> auto& = delete;

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
        throw bad_https(result.error(), "Internal failure");
    auto response = result.value();
    if(result.error() != error::Success)
        throw bad_https(result.error(), status_message(response.status));
    return response;
}

inline auto get_client(std::shared_ptr<SSLClient> ctx, const std::string& path) {
    auto result = ctx->Get(path);
    if(!result)
        throw bad_https(result.error(), "Internal failure");
    auto response = result.value();
    if(result.error() != error::Success)
        throw bad_https(result.error(), status_message(response.status));
    return response;
}

inline auto make_client(const std::string& uri) {
    return std::make_shared<Client>(uri);
}

inline auto make_client(const std::string& host, uint16_t port) {
    return std::make_shared<SSLClient>(host, port);
}
}   // end namespace

#endif
