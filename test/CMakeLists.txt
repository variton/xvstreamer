#========================== err namespace tests ========================== 

add_executable(test_err
    test_err_hdr.cpp
)

target_include_directories(test_err PUBLIC
  $<BUILD_INTERFACE:${tcxx-23_SOURCE_DIR}/include/err>
  $<BUILD_INTERFACE:${CMAKE_INCLUDE_PATH}/core>
  $<BUILD_INTERFACE:${CMAKE_INCLUDE_PATH}/topology>
  $<INSTALL_INTERFACE:include>
)

# target_link_libraries(test_err
#   PRIVATE
#     PkgConfig::GSTREAMER
# )

target_link_libraries(test_err PRIVATE
    doctest::doctest
    PkgConfig::GSTREAMER
)

target_link_options(test_err PRIVATE
                    $<$<CONFIG:Debug>:--coverage>)

target_compile_options(test_err PRIVATE 
                       -Wall -Wextra -pedantic
                       $<$<CONFIG:Debug>:--coverage -Og -g>
                       $<$<CONFIG:Release>:-O3 -DNDEBUG>)

add_test(NAME test_err COMMAND $<TARGET_FILE:test_err>)

set_tests_properties(test_err PROPERTIES
  ENVIRONMENT "RC=${TRC}"
)


