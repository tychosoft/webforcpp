// Copyright (C) 2024 Tycho Softworks.
// This code is licensed under MIT license.

#ifndef WEB_IPINFO_HPP_
#define WEB_IPINFO_HPP_

#include "https.hpp"

namespace web {
class ipinfo_t final {
public:
    ipinfo_t(const ipinfo_t& from) = default;
    ipinfo_t(bool ssl = true) :
    client_(https::make_client((ssl ? "https://" : "http://") + host())) {}

    void close() {
        client_->stop();
    }

    void set_token(const std::string& token) {
        token_ = token;
    }

    auto get(const std::string& address, const std::string& type = "json") {
        auto query = "/" + address + "/" + type;
        if(!token_.empty())
            query += "?token=" + token_;
        auto resp = https::get_client(*client_, query);
        return resp;
    }

    static auto host() -> std::string {
        return {"ipinfo.io"};
    }

private:
    std::string token_;
    std::shared_ptr<https::Client> client_;
};
}   // end namespace
#endif
