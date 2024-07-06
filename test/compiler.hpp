// Copyright (C) 2020 Tycho Softworks.
// This code is licensed under MIT license.

#ifndef	COMPILER_HPP_
#define	COMPILER_HPP_

#ifdef __clang__
#pragma clang diagnostic ignored "-Wpadded"
#pragma clang diagnostic ignored "-Wswitch-enum"
#pragma clang diagnostic ignored "-Wweak-vtables"
#pragma clang diagnostic ignored "-Wunused-member-function"
#endif

#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wunused-result"
#pragma GCC diagnostic ignored "-Wzero-as-null-pointer-constant"
#endif

#if !defined(_MSC_VER) && __cplusplus < 201703L
#error C++17 compliant compiler required
#endif

#include <cassert>
#include <cstdint>
#endif
