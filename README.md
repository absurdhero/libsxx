# libsxx

This is a reference counted S-expression library for C++.
libsxx has no external dependencies.

S-expression implementations for C and C++ are often tied
closely to a specific scheme or lisp implementation.
The shared nature of s-expressions makes it difficult to
have powerful yet safe memory management without a
garbage collector. libsxx uses C++11's `shared_ptr` to
implement automatic reference counting with reasonable
performance and, most importantly, it doesn't require
complex strategies when sharing portions of an s-expression
between different parts of your code.

## Building

Requires cmake 2.8 or above and a compiler that supports C++14.
The project has been tested on gcc 5.4 on Ubuntu 16.04.

The included `configure.sh` generates a cmake build in the
`build` directory. On windows, use the cmake GUI to generate
the project.

`build.sh` runs make inside the `build` directory and then
runs the tests.

## References and Inspirations

[The Scheme Reports](http://www.scheme-reports.org)

The most comprehensive reference of s-expression operations.

[jackson-core](https://github.com/FasterXML/jackson-core)

Powerful serialization/deserialization library for Java
with pluggable parsing and a great traversal API.

[JSON for Modern C++](https://github.com/nlohmann/json)

A header-only JSON library with a convenient API and STL container compatibility.
