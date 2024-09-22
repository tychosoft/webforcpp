# Copyright (C) 2024 Tycho Softworks.
#
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without
# modifications, as long as this notice is preserved.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

cmake_minimum_required(VERSION 3.16.0)
project(WebForCPP VERSION 0.1.1 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

file(GLOB LINT_SOURCES
    RELATIVE ${PROJECT_SOURCE_DIR}
    src/*.hpp test/*.cpp)
list(REMOVE_ITEM LINT_SOURCES src/https.hpp src/http.hpp)

include(cmake/custom.cmake OPTIONAL)
include(cmake/project.cmake)
include(cmake/features.cmake)
include(cmake/coverage.cmake)
include(cmake/linting.cmake)
include(cmake/deploy.cmake OPTIONAL)

file(GLOB optional .git[a-z]* *.json *.in *.yml .clang* cmake/*)
file(GLOB markdown *.md)
file(GLOB headers src/*.hpp src/*.h)

# Setup headers
include_directories(${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/src)
configure_file(webforcpp.pc.in webforcpp.pc)

# Testing
enable_testing()
add_executable(test_json test/json.cpp src/json.hpp)
add_test(NAME test-json COMMAND test_json)

add_executable(test_https test/https.cpp src/https.hpp)
target_link_libraries(test_https PRIVATE OpenSSL::SSL OpenSSL::Crypto)
add_test(NAME test-https COMMAND test_https)

add_executable(try_ipinfo test/ipinfo.cpp src/ipinfo.hpp)
target_link_libraries(try_ipinfo PRIVATE OpenSSL::SSL OpenSSL::Crypto)

# Extras...
add_custom_target(header-files SOURCES ${headers})
add_custom_target(support-files SOURCES ${markdown} ${optional})

install(FILES ${headers} DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/webforcpp")
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/webforcpp.pc DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig")
