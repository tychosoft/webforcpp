# About WebForCPP

This package offers modern web access using header-only libraries for C++17.
This includes the httplib.h header-only library for http(s) clients and
servers, and a linted sajson.h for json parsing. In addition, supplemental
header-only libraries that access various specific web api services will also
be added. The core dependencies only required C++11, but our extensions and
api headers may only support C++17 and later.

This choice of using httplib and sajson was for very generic cross-platform
functionality, https functionality built around openssl, and broad licensing
compatibility. The collective work functions in effect on a MIT license, which
httplib and any additional api headers use. The sajson license is fully
permissive as long as the copyright notice is kept in the sajson header.

WebForCPP requires CMake to build. It should build and work with GCC (9 or
later), with Clang (14? or later), and MSVC.  Besides GNU/Linux and BSD
systems, webforcpp is portable to and can support the MingW platform target as
installed by Debian when selecting posix runtime, and even native MS Visual
Studio builds. The minimum requirement is a C++17 compiler (or later).

Httplib uses blocking I/O, which means http requests launched in threads may
block waiting for I/O completion. The simplest way to unblock an outstanding
api request early is probably to force close the httplib client context stop()
method from another thread. This and other interruptions may generate a SIGPIPE
on posix platforms, which likely should be ignored. The individual API headers
may have a make\_XXX function to create an exposed client context in a shared
pointer that can then be used for forced closure and a separate api request
function that uses a client context which can be handed off to a client thread.

## Dependencies

Webforcpp uses openssl for crypto operations and https related functionality.
In addition, C++ thread support may have to be enabled to use C++ thread
operations. The cmake/features.cmake file shows how to test for and enable
these dependencies correctly from CMake.

## Distributions

Distributions of this package are provided as detached source tarballs made
from a tagged release from our public gitlab repository or by building the dist
target. These stand-alone detached tarballs can be used to make packages for
many GNU/Linux systems, and for BSD ports. They may also be used to build and
install the software directly on a target platform.

The latest public release source tarball can be produced by an auto-generated
tarball from a tagged release in the projects public git repository at
https://gitlab.com/tychosoft/webforcpp. Webforcpp can also be easily vendored
in other software using git modules from this public repo. I also package
Webforcpp for Alpine Linux. There is no reason this cannot easily be packaged
for use on other distributions, for BSD ports, vcpkg, etc, as well.

## Participation

This project is offered as free (as in freedom) software for public use and has
a public project page at https://www.gitlab.com/tychosoft/webforcpp which has
an issue tracker where people can submit public bug reports and a public git
repository. Patches and merge requests may be submitted in the issue tracker
or thru email. Support requests and other kinds of inquiries may also be sent
thru the tychosoft gitlab help desktop service. Other details about
participation may be found in CONTRIBUTING.md.

## Testing

There are testing programs for each header. These run simple tests that will be
expanded to improve code coverage over time. The test programs are the only
built target making this library by itself, and the test programs in this
package work with the cmake ctest framework. They may also be used as simple
examples of how a given header works. There is also a **lint** target that can
be used to verify code changes.
