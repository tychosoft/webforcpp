# Features

WebForCPP consists of a series of header files for core web functionality, and
to offer common web api's that will be collected over time. The use of a header
only library makes it very efficient to mix and match different api headers as
needed without having either different libraries or a single library with
mostly unused code.

This package builds unit test applications for ctest and some example
applications you can try.

## Core services

These provide the core functionality of webforcpp for http network access and
json parsing. The http network access supports servers with path parsing
rules.

### http.hpp and https.hpp

Cross-platform http and https c++ client and server support. This matches well
with moderncli header libraries, and offers special types for modern context
programming above httplib.h.

### json.hpp

A fast and efficient json parser. This is meant for web api's that use json. A
number of convenience methods have been added to sajason.h to make it easer to
express and use.

## API servers

Each supported internet api will be given it's own header in webforcpp. These
may access, post, and return json data and text bodies.

### ipinfo.hpp

Provides a minimal api to optionally use tokens for authorization to access
ipinfo.io json and individual fields from C++. This may be expanded further in
the future.

