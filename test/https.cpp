// Copyright (C) 2024 Tycho Softworks.
// This code is licensed under MIT license.

#undef  NDEBUG
#include "compiler.hpp"     // IWYU pragma: keep
#include "https.hpp"
#include "http.hpp"         // mostly to compile check...

auto main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) -> int { // NOLINT
    auto client = web::https::make_client("https://localhost");
}

