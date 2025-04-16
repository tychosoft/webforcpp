// Copyright (C) 2024 Tycho Softworks.
// This code is licensed under MIT license.

#undef  NDEBUG
#include "compiler.hpp"     // IWYU pragma: keep
#include "json.hpp"

auto main([[maybe_unused]] int argc, [[maybe_unused]] char **argv) -> int {
    using namespace web::json;

    const ast_t ast1, ast2;

    char text[] = R"({"name":"test","value":2})";
    const auto& json1 = parse(*ast1, make_view(text));
    assert(json1.is_valid());

    const auto& root = *json1;
    assert(root.is_object());

    const auto& name = root("name");
    assert(name.is_string());
    assert(name.to_string() == "test");

    const auto& test = root.at("test");
    assert(!test);

    const std::string s2(text);
    const auto& json2 = parse(*ast2, make_view(s2));
    assert(json2.is_valid());

    try {
        const spec_t spec = {"name", "age", "dead"};
        const auto out = make_json(spec, "David", 20, false);
        assert(out == R"({"name":"David","age":20,"dead":false})");
        assert(make_objects(spec, false) == "[name,age,dead]");
        assert(make_array(spec, false) == R"(["name","age","dead"])");
    }
    catch(...) {
        return -1;
    }
}
