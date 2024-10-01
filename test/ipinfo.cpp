// Copyright (C) 2024 Tycho Softworks.
// This code is licensed under MIT license.

#undef  NDEBUG
#include "compiler.hpp"     // IWYU pragma: keep
#include "ipinfo.hpp"

auto main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) -> int { // NOLINT
    web::ipinfo_t ipinfo;
    try {
        auto response = ipinfo.get("1.1.2.2");
        std::cout << response.body << std::endl;
        response = ipinfo.get("1.2.2.1", "city");
        std::cout << response.body << std::endl;
    }
    catch(const std::exception& e) {
        std::cerr << "Error: " << e.what();
    }
}