# xvstreamer

`xvstreamer` is a C++23 media streaming playground built on top of
GStreamer. The project currently provides a small video stream wrapper,
GStreamer resource-management helpers, environment utilities, tests, coverage
support, and Doxygen documentation wiring.

## Features

- C++23 codebase configured with CMake and Ninja.
- GStreamer-backed `xstream::Stream<xstream::Video>` wrapper for initializing,
  starting, and releasing a `playbin` pipeline.
- RAII helpers for common GStreamer object lifetimes.
- Utility library for environment-variable access.
- Doctest-based unit tests with CTest integration.
- Optional lcov/genhtml coverage target.
- Optional Doxygen API documentation target.

## Repository Layout

```text
.
|-- CMakeLists.txt          # Top-level CMake project
|-- build.sh                # Debug/release build helper
|-- cmake/                  # Dependency, coverage, and docs CMake modules
|-- docs/                   # Doxygen configuration template
|-- include/                # Public headers
|   |-- utils/              # Environment utilities
|   |-- xvscore/            # Error and GStreamer memory helpers
|   `-- xstream/            # Stream/video abstractions
|-- rc/                     # Runtime test media
|-- src/                    # Libraries and executable targets
|   |-- player/             # Development GStreamer player executable
|   `-- utils/              # Utility library implementation and tests
`-- test/                   # Core stream and helper tests
```

## Requirements

The default build expects the following tools and libraries:

- CMake 4.2.3 or newer
- Ninja
- GCC 15 (`g++-15`)
- pkg-config
- GStreamer 1.0 development package
- spdlog development package
- lcov and genhtml
- gcov
- Git access for FetchContent dependencies

On Debian or Ubuntu, the system packages are typically:

```bash
sudo apt install cmake ninja-build pkg-config g++-15 \
  libgstreamer1.0-dev libspdlog-dev lcov
```

The CMake configuration fetches these source dependencies into `.deps/` when
they are not already cached:

- `tcxx-23` from `https://github.com/variton/tcxx-23.git`
- `doctest` v2.4.12 from `https://github.com/doctest/doctest.git`

## Build

Use the project build helper from the repository root:

```bash
./build.sh debug
```

For an optimized build:

```bash
./build.sh release
```

The script configures CMake, builds the selected configuration, and runs the
test suite. Build artifacts are written under `build/debug` or
`build/release`; runtime targets are emitted to `bin/`, and shared libraries to
`lib/`.

Equivalent manual CMake commands:

```bash
cmake -S . -B build/debug -G Ninja \
  -DCMAKE_BUILD_TYPE=Debug \
  -DCMAKE_CXX_COMPILER=g++-15 \
  -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

cmake --build build/debug -j "$(nproc)"
ctest --test-dir build/debug --output-on-failure
```

## Tests

Tests are registered with CTest and use doctest:

```bash
ctest --test-dir build/debug --output-on-failure
```

The video tests use the sample file in `rc/sintel_trailer-H265bq.mp4`. CMake
sets the `RC` environment variable for registered tests so they can locate this
asset.

## Coverage

Debug builds include coverage flags. After configuring a debug build, generate
an HTML coverage report with:

```bash
cmake --build build/debug --target coverage
```

The generated report is written to:

```text
build/debug/coverage_html/
```

## Documentation

If Doxygen is installed, CMake enables a `doxygen` target:

```bash
cmake --build build/debug --target doxygen
```

The build helper can also request documentation generation:

```bash
./build.sh debug -d
```

Generated HTML documentation is written under `docs/html`.

## Static Analysis

The build helper can run static-analysis tools after the build and tests:

```bash
./build.sh debug -a
```

This invokes `run-clang-tidy` and `scan-build` against the generated compile
database.

## Cleaning

```bash
./build.sh clean
./build.sh clean-debug
./build.sh clean-release
```

## Runtime Notes

The `player` target is a development executable that creates a GStreamer
`playbin` pipeline. The current implementation uses a hard-coded media URI in
`src/player/main.cpp`, while the reusable video stream wrapper accepts a video
path through `xstream::Stream<xstream::Video>::init(...)`.

The main reusable API is header-based under `include/xstream/`:

```cpp
#include <video.h>

xstream::Stream<xstream::Video> stream;
auto init = stream.init("/absolute/path/to/video.mp4");
if (!init) {
  // inspect init.error()
}

auto started = stream.start();
if (!started) {
  // inspect started.error()
}

stream.release();
```

## License

This project is licensed under the MIT License. See [LICENSE](LICENSE) for the
full license text.
