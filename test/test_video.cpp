
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest/doctest.h>

#include <video.h>
#include <string>
#include <env_mgr.h>

TEST_CASE("test_video_init") {
  auto & env = utils::EnvMgr::get_instance();
  auto rc = env.get_envv("RC");
  std::string video{"sintel_trailer-H265bq.mp4"};
  std::string video_file_path{rc.value()+"/"+video};
  stream::StreamTraits<stream::Video> video_stream; 
  auto ret = video_stream.init(video_file_path);
  REQUIRE(ret.has_value());
  CHECK(video_stream.get_pipeline() != nullptr);
}
