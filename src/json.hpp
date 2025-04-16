// Copyright (C) 2024 Tycho Softworks.
// This code is licensed under MIT license.

#ifndef WEB_JSON_HPP_
#define WEB_JSON_HPP_

#include "sajson.h"

#include <sstream>
#include <vector>
#include <string_view>
#include <stdexcept>

namespace web::json {
using namespace sajson;
using node_t = sajson::value;
using spec_t = std::vector<std::string>;

// Additional special functions we may add...

class ast_t final {
public:
    ast_t(const ast_t&) = delete;
    auto operator=(const ast_t&) -> ast_t& = delete;

    explicit ast_t(std::size_t size = 500) :
    data_(new std::size_t[size]), size_(size) {}

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
    std::size_t *data_{nullptr};
    std::size_t size_{0};
};

template <typename T>
inline void _make_field(std::ostringstream& out, const std::string& key, const T& value, bool& first) {
    if(!first) {
        out << ",";
    }
    else {
        first = false;
    }

    out << "\"" << key << "\":";
    if constexpr (std::is_convertible_v<T, std::string>) {
        out << "\"" << value << "\"";
    }
    else if  constexpr (std::is_same_v<T, bool>) {
        out << (value ? "true" : "false");
    }
    else {
        out << value;
    }
}

template <typename... Args>
inline auto make_json(const spec_t& spec, Args... args) {
    if (spec.size() != sizeof...(args)) throw std::invalid_argument("Number of arguments does not match the JSON specification.");

    std::ostringstream out;
    out << "{";
    auto first = true;
    auto it = spec.begin();

    // Expand variadic arguments in order
    ([&]() {
        _make_field(out, *it, args, first);
        ++it;
    }(), ...);

    out << "}";
    return out.str();
}

template<typename T>
inline auto make_array(const std::vector<T>& list, bool nl = false) {
    std::ostringstream out;
    auto count = size_t(0);
    out << "[";
    if(nl)
        out << std::endl;
    for(const auto& value : list) {
        if constexpr (std::is_convertible_v<T, std::string>) {
            out << "\"" << value << "\"";
        }
        else if  constexpr (std::is_same_v<T, bool>) {
            out << (value ? "true" : "false");
        }
        else {
            out << value;
        }
        if(++count < list.size())
            out << ",";
        if(nl)
            out << std::endl;
    }
    out << "]";
    if(nl)
        out << std::endl;
    return out.str();
}

template<typename T>
inline auto make_objects(const std::vector<T>& list, bool nl = true) {
    std::ostringstream out;
    auto count = size_t(0);
    out << "[";
    if(nl)
        out << std::endl;
    for(const auto& value : list) {
        out << value;
        if(++count < list.size())
            out << ",";
        if(nl)
            out << std::endl;
    }
    out << "]";
    if(nl)
        out << std::endl;
    return out.str();
}

inline auto data_view(char *text, std::size_t size = 0) {
    if(!size)
        size = strlen(text);   // FlawFinder: ignore
    return mutable_string_view(size, text);
}

inline auto make_view(const char *text, std::size_t size = 0) {
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
