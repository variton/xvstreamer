
add_executable(test_env_mgr
    test_env_mgr.cpp
)

target_include_directories(test_env_mgr PUBLIC
  $<BUILD_INTERFACE:${tcxx-23_SOURCE_DIR}/include/core>
  $<BUILD_INTERFACE:${tcxx-23_SOURCE_DIR}/include/err>
  $<BUILD_INTERFACE:${CMAKE_INCLUDE_PATH}/utils>
  $<INSTALL_INTERFACE:include>
)

target_link_libraries(test_env_mgr PRIVATE
                      utils 
                      doctest::doctest)

target_link_options(test_env_mgr PRIVATE
                    $<$<CONFIG:Debug>:--coverage>)

target_compile_options(test_env_mgr PRIVATE
                       -Wall -Wextra -pedantic
                       $<$<CONFIG:Debug>:--coverage -Og -g>
                       $<$<CONFIG:Release>:-O3 -DNDEBUG>)

add_test(NAME test_env_mgr COMMAND $<TARGET_FILE:test_env_mgr>)

set_tests_properties(test_env_mgr PROPERTIES
  ENVIRONMENT "RC=${TRC}"
)
