// Copyright (C) 2024 Tycho Softworks.
// This code is licensed under MIT license.

#ifndef WEB_JSON_HPP_
#define WEB_JSON_HPP_

#include "sajson.h"

#include <string_view>
#include <memory>

namespace web::json {
using namespace sajson;
using node_t = sajson::value;

// Additional special functions we may add...

class ast_t final {
public:
    ast_t(const ast_t&) = delete;
    auto operator=(const ast_t&) -> ast_t& = delete;

    explicit ast_t(size_t size = 500) :
    data_(new size_t[size]), size_(size) {}

    ~ast_t() {
        delete[] data_;
    }

    auto operator *() const {
        return bounded_allocation(data_, size_);
    }

    auto size() const noexcept {
        return size_;
    }

private:
    size_t *data_{nullptr};
    size_t size_{0};
};

inline auto data_view(char *text, size_t size = 0) {
    if(!size)
        size = strlen(text);   // FlawFinder: ignore
    return mutable_string_view(size, text);
}

inline auto make_view(const char *text, size_t size = 0) {
    if(!size)
        size = strlen(text);   // FlawFinder: ignore
    return mutable_string_view(sajson::string(text, size));
}

inline auto make_view(const std::string_view& s) {
    return mutable_string_view(sajson::string(s.data(), s.size()));
}

inline auto make_string(const std::string_view& s) {
    return sajson::string(s.data(), s.size());
}
} // end namespace
#endif
