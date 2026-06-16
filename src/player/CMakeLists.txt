
add_executable(player
    main.cpp
)

target_include_directories(player PUBLIC
  $<BUILD_INTERFACE:${tcxx-23_SOURCE_DIR}/include/err>
  $<BUILD_INTERFACE:${tcxx-23_SOURCE_DIR}/include/core>
  $<BUILD_INTERFACE:${CMAKE_INCLUDE_PATH}/xstream>
  $<BUILD_INTERFACE:${CMAKE_INCLUDE_PATH}/xvscore>
  $<BUILD_INTERFACE:${CMAKE_INCLUDE_PATH}/topology>
  $<INSTALL_INTERFACE:include>
)

target_link_libraries(player PRIVATE
    PkgConfig::GSTREAMER
)

target_link_options(player PRIVATE 
                    $<$<CONFIG:Debug>:--coverage>)

target_compile_options(player PRIVATE 
                       -Wall -Wextra -pedantic
                       $<$<CONFIG:Debug>:--coverage -Og -g>
                       $<$<CONFIG:Release>:
                            -O3 
                            -DNDEBUG
                            -march=native
                            -mtune=native
                            -funroll-loops
                            -fomit-frame-pointer>)
