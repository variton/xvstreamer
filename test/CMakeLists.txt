#========================== core namespace tests ========================== 

#========================== error_hdr tests ===============================
add_executable(test_error_hdr
    test_error_hdr.cpp
)

target_include_directories(test_error_hdr PUBLIC
  $<BUILD_INTERFACE:${tcxx-23_SOURCE_DIR}/include/err>
  $<BUILD_INTERFACE:${CMAKE_INCLUDE_PATH}/xvscore>
  $<BUILD_INTERFACE:${CMAKE_INCLUDE_PATH}/topology>
  $<INSTALL_INTERFACE:include>
)

target_link_libraries(test_error_hdr PRIVATE
    doctest::doctest
    PkgConfig::GSTREAMER
)

target_link_options(test_error_hdr PRIVATE
                    $<$<CONFIG:Debug>:--coverage>)

target_compile_options(test_error_hdr PRIVATE 
                       -Wall -Wextra -pedantic
                       $<$<CONFIG:Debug>:--coverage -Og -g>
                       $<$<CONFIG:Release>:-O3 -DNDEBUG>)

add_test(NAME test_error_hdr COMMAND $<TARGET_FILE:test_error_hdr>)

set_tests_properties(test_error_hdr PROPERTIES
  ENVIRONMENT "RC=${TRC}"
)

#========================== gst_memory tests ==============================
add_executable(test_gst_memory
    test_gst_memory.cpp
)

target_include_directories(test_gst_memory PUBLIC
  $<BUILD_INTERFACE:${tcxx-23_SOURCE_DIR}/include/err>
  $<BUILD_INTERFACE:${tcxx-23_SOURCE_DIR}/include/core>
  $<BUILD_INTERFACE:${CMAKE_INCLUDE_PATH}/xvscore>
  $<BUILD_INTERFACE:${CMAKE_INCLUDE_PATH}/utils>
  $<BUILD_INTERFACE:${CMAKE_INCLUDE_PATH}/topology>
  $<INSTALL_INTERFACE:include>
)

target_link_libraries(test_gst_memory PRIVATE
    utils
    doctest::doctest
    PkgConfig::GSTREAMER
)

target_link_options(test_gst_memory PRIVATE
                    $<$<CONFIG:Debug>:--coverage>)

target_compile_options(test_gst_memory PRIVATE 
                       -Wall -Wextra -pedantic
                       $<$<CONFIG:Debug>:--coverage -Og -g>
                       $<$<CONFIG:Release>:-O3 -DNDEBUG>)

add_test(NAME test_gst_memory COMMAND $<TARGET_FILE:test_gst_memory>)

set_tests_properties(test_gst_memory PROPERTIES
  ENVIRONMENT 
    "RC=${TRC}"
)

#========================== stream namespace tests =======================

#=============================== video tests =============================
add_executable(test_video
    test_video.cpp
)

target_include_directories(test_video PUBLIC
  $<BUILD_INTERFACE:${tcxx-23_SOURCE_DIR}/include/err>
  $<BUILD_INTERFACE:${tcxx-23_SOURCE_DIR}/include/core>
  $<BUILD_INTERFACE:${CMAKE_INCLUDE_PATH}/xstream>
  $<BUILD_INTERFACE:${CMAKE_INCLUDE_PATH}/utils>
  $<BUILD_INTERFACE:${CMAKE_INCLUDE_PATH}/xvscore>
  $<BUILD_INTERFACE:${CMAKE_INCLUDE_PATH}/topology>
  $<INSTALL_INTERFACE:include>
)

target_link_libraries(test_video PRIVATE
    utils
    doctest::doctest
    PkgConfig::GSTREAMER
)

target_link_options(test_video PRIVATE
                    $<$<CONFIG:Debug>:--coverage>)

target_compile_options(test_video PRIVATE 
                       -Wall -Wextra -pedantic
                       $<$<CONFIG:Debug>:--coverage -Og -g>
                       $<$<CONFIG:Release>:-O3 -DNDEBUG>)

add_test(NAME test_video COMMAND $<TARGET_FILE:test_video>)

set_tests_properties(test_video PROPERTIES
  ENVIRONMENT "RC=${TRC}"
)
