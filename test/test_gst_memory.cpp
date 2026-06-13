
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest/doctest.h>

#include <gst_memory.h>
#include <gst/gst.h>
#include <string>
#include <env_mgr.h>

TEST_CASE("test_gst_memory_GstElement") {
  auto & env = utils::EnvMgr::get_instance();
  auto rc = env.get_envv("RC");
  std::string video{"sintel_trailer-H265bq.mp4"};
  std::string description = "playbin uri=file://"+rc.value()+"/"+video;
  gst_init(nullptr, nullptr); 
  GError* raw_error = nullptr;

  auto pipeline = core::GstPtr<GstElement>{
    gst_parse_launch(description.c_str(), &raw_error)
  };

  auto error = core::GstPtr<GError>{raw_error}; 

  REQUIRE(pipeline != nullptr);
  REQUIRE(error == nullptr);
}

// TEST_CASE("test_gst_memory_GstElement fail") {
//   auto & env = utils::EnvMgr::get_instance();
//   auto rc = env.get_envv("RC");
//   std::string description = "playbin uri=file://";
//   gst_init(nullptr, nullptr); 
//   GError* raw_error = nullptr;
//   auto pipeline = core::GstPtr<GstElement>{
//     gst_parse_launch(description.c_str(), &raw_error)
//   };

//   auto error = core::GstPtr<GError>{raw_error}; 
 
//   REQUIRE(pipeline != nullptr);
//   REQUIRE(error == nullptr);
// }
