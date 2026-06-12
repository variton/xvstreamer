
find_package(PkgConfig REQUIRED)

pkg_check_modules(GSTREAMER REQUIRED IMPORTED_TARGET gstreamer-1.0)
# pkg_check_modules(GSTREAMER REQUIRED
#     gstreamer1.0-x 
#     libgstreamer1.0-0 
# )

find_package(spdlog)
if(NOT spdlog_FOUND)
    message(FATAL_ERROR
        "libspdlog-dev not found.\n"
        "On Debian/Ubuntu, install it with:\n"
        "  sudo apt install libspdlog-dev"
    )
endif()

find_program(LCOV_EXECUTABLE lcov)
find_program(GENHTML_EXECUTABLE genhtml)

if(NOT LCOV_EXECUTABLE OR NOT GENHTML_EXECUTABLE)
    message(FATAL_ERROR
        "lcov/genhtml not found.\n"
        "On Debian/Ubuntu, install it with:\n"
        "  sudo apt install lcov"
    )
endif()

find_program(GCOV_EXECUTABLE gcov)

if(NOT GCOV_EXECUTABLE)
    message(FATAL_ERROR
        "lcov/genhtml not found.\n"
        "On Debian/Ubuntu, install it with:\n"
        "  sudo apt install gcov"
    )
endif()
