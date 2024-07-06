// Copyright (C) 2024 Tycho Softworks.
// This code is licensed under MIT license.

#undef  NDEBUG
#define CPPHTTPLIB_OPENSSL_SUPPORT 1    // NOLINT
#include "compiler.hpp"
#include "https.hpp"

auto main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) -> int {
    auto client = web::https::make_client("localhost");
}

