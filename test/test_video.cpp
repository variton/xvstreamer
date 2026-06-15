
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest/doctest.h>

#include <video.h>
#include <env_mgr.h>

#include <string>
#include <optional>

struct EnvFixture{
  
  EnvFixture(){
    auto & env = utils::EnvMgr::get_instance();
    auto rc = env.get_envv("RC");
    video_file_path=rc.value()+"/"+video;
  } 

  std::optional<std::string> rc{std::nullopt}; 
  std::string video{"sintel_trailer-H265bq.mp4"};
  std::string video_file_path;
};

TEST_CASE_FIXTURE(EnvFixture,"test_video_init") {
  xstream::Stream<xstream::Video> video_stream; 
  auto ret = video_stream.init(video_file_path);
  REQUIRE(ret.has_value());
  CHECK(video_stream.get_pipeline() != nullptr);
}

TEST_CASE_FIXTURE(EnvFixture,"test_video_start") {
  xstream::Stream<xstream::Video> video_stream; 
  auto ret = video_stream.init(video_file_path);
  REQUIRE(ret.has_value());
  CHECK(video_stream.get_pipeline() != nullptr);
  ret = video_stream.start();
  REQUIRE(ret.has_value());
}

TEST_CASE_FIXTURE(EnvFixture,"test_video_release") {
  xstream::Stream<xstream::Video> video_stream; 
  auto ret = video_stream.init(video_file_path);
  REQUIRE(ret.has_value());
  CHECK(video_stream.get_pipeline() != nullptr);
  ret = video_stream.start();
  REQUIRE(ret.has_value());
  ret = video_stream.release();
  REQUIRE(ret.has_value());
}
