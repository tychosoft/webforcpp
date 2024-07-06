# Features

WebForCPP consists of a series of header files for core web functionality, and
to offer common web api's that will be collected over time. The use of a header
only library makes it very efficient to mix and match different api headers as
needed without having either different libraries or a single library with
mostly unused code.

## httplib.h

Cross-platform http and https c++ client and server support. This matches well
with moderncli header libraries.

## sajason.h

A fast and efficient json parser. This is meant for web api's that use json.

