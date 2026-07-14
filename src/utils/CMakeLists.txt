
add_library(utils SHARED 
            env_mgr.cpp)

target_include_directories(utils PUBLIC
  $<BUILD_INTERFACE:${tcxx-23_SOURCE_DIR}/include/core>
  $<BUILD_INTERFACE:${tcxx-23_SOURCE_DIR}/include/err>
  $<BUILD_INTERFACE:${tcxx-23_SOURCE_DIR}/include/topology>
  $<BUILD_INTERFACE:${CMAKE_INCLUDE_PATH}/utils>
  $<INSTALL_INTERFACE:include>
)

target_link_options(utils PRIVATE 
                    $<$<CONFIG:Debug>:--coverage>)

target_compile_options(utils PRIVATE 
                       -Wall -Wextra -pedantic
                       $<$<CONFIG:Debug>:--coverage -Og -g>
                       $<$<CONFIG:Release>:-O3 -DNDEBUG>)

add_subdirectory(test)
