// Copyright (C) 2024 Tycho Softworks.
// This code is licensed under MIT license.

#undef  NDEBUG
#include "compiler.hpp"     // IWYU pragma: keep
#include "https.hpp"

// Mostly to compile-check inclusion with https...
#include "http.hpp"         // IWYU pragma: keep

auto main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) -> int { // NOLINT
    auto client = web::https::make_client("https://localhost");
}

