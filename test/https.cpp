// Copyright (C) 2024 Tycho Softworks.
// This code is licensed under MIT license.

#undef  NDEBUG
#include "compiler.hpp"     // IWYU pragma: keep
#include "https.hpp"
#include "utils.hpp"

// Mostly to compile-check inclusion with https...
#include "http.hpp"         // IWYU pragma: keep

auto main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) -> int { // NOLINT
    auto client = web::https::make_client("https://localhost");
    auto addr = web::net_address("127.0.0.1");
    assert(*addr == "127.0.0.1");

    auto addr1 = web::net_address("x!yz");
    assert((*addr1).empty());
    assert(!addr1);
}
