
include(FetchContent)

set(FETCHCONTENT_BASE_DIR
    "${CMAKE_SOURCE_DIR}/.deps"
    CACHE PATH "FetchContent cache"
    FORCE
)

#tcxx-23 ========================================================

set(TCXX_23_SOURCE_DIR "${FETCHCONTENT_BASE_DIR}/tcxx-23-src")

if(EXISTS "${TCXX_23_SOURCE_DIR}/CMakeLists.txt")
    message(STATUS "Using cached tcxx_23: ${TCXX_23_SOURCE_DIR}")

    set(FETCHCONTENT_SOURCE_DIR_TCXX_23
        "${TCXX_23_SOURCE_DIR}"
        CACHE PATH "Cached tcxx-23 source"
        FORCE
    )
else()
    message(STATUS "Fetching tcxx-23")
endif()

FetchContent_Declare(
    tcxx-23
    GIT_REPOSITORY https://github.com/variton/tcxx-23.git
    GIT_TAG main
    GIT_SHALLOW TRUE

    # Prevent tcxx's own CMakeLists.txt from being included
    SOURCE_SUBDIR cmake-do-not-add
)

FetchContent_MakeAvailable(tcxx-23)

#doctest =======================================================

set(DOCTEST_SOURCE_DIR "${FETCHCONTENT_BASE_DIR}/doctest-src")

if(EXISTS "${DOCTEST_SOURCE_DIR}/CMakeLists.txt")
    message(STATUS "Using cached doctest: ${DOCTEST_SOURCE_DIR}")

    set(FETCHCONTENT_SOURCE_DIR_DOCTEST
        "${DOCTEST_SOURCE_DIR}"
        CACHE PATH "Cached doctest source"
        FORCE
    )
else()
    message(STATUS "Fetching doctest")
endif()

FetchContent_Declare(
    doctest
    GIT_REPOSITORY https://github.com/doctest/doctest.git
    GIT_TAG v2.4.12
)

FetchContent_MakeAvailable(doctest)
