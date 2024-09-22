// Copyright (C) 2024 Tycho Softworks.
// This code is licensed under MIT license.

// NOTE: This is not meant to be directly included, but rather provides
// common client functions.

#ifndef WEB_CLIENT_HELPER_HPP_
#define WEB_CLIENT_HELPER_HPP_

// Client functions we add...

using error = httplib::Error;
class bad_client final : public std::exception {
public:
    bad_client() = delete;
    bad_client(const bad_client& other) = default;
    explicit bad_client(error code, const char *msg) : err_(code), msg_(msg) {}
    auto operator=(const bad_client&) -> auto& = delete;

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

inline auto get_client(Client& ctx, const std::string& path) {
    auto result = ctx.Get(path);
    if(!result)
        throw bad_client(result.error(), "Internal failure");
    auto response = result.value();
    if(result.error() != error::Success)
        throw bad_client(result.error(), status_message(response.status));
    return response;
}

inline auto make_client(const std::string& uri) {
    return std::make_shared<Client>(uri);
}
#endif
