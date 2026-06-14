
#include <video.h>
#include <error_hdr.h>

namespace stream {
//todo include video config Config<Video> -> should container the description for the video pipeline
inline StreamTraits<Video>::StreamTraits() noexcept
  : pipeline_{nullptr}
  , bus_{nullptr}
  //, message_{nullptr}
{}

inline std::expected<void, VideoErrorInfo>
StreamTraits<Video>::init(const std::string & video_file_path, int argc, char ** argv) noexcept
{
  (argc == 0 && argv == nullptr)? gst_init(nullptr,nullptr):gst_init(&argc, &argv);
  GError * raw_error{nullptr};
  std::string pipeline_description = "playbin uri=file://"+video_file_path;
  pipeline_ = xvscore::GstPtr<GstElement>{gst_parse_launch(pipeline_description.c_str(), &raw_error)};
  if (!pipeline_.get()){
    return xvscore::unexpected(VideoError::PipelineInitFailed, raw_error);
  }
  xvscore::GstPtr<GError> error{xvscore::GstPtr<GError>{raw_error}};
  //GstMessage will be used in the future to handle async events
  return {};
}

inline std::expected<void, VideoErrorInfo>
StreamTraits<Video>::start() noexcept
{
  gst_element_set_state(pipeline_.get(),GST_STATE_PLAYING);
  bus_= xvscore::GstPtr<GstBus>(gst_element_get_bus(pipeline_.get()));;
  if(!bus_.get()){
    std::string message{"bus has not been created"};
    return err::unexpected(VideoError::BusInitFailed, message);
  }
  // auto lgst_err= GST_MESSAGE_ERROR | GST_MESSAGE_EOS;
  // message_=gst_bus_timed_pop_filtered(bus_, GST_CLOCK_TIME_NONE,(GstMessageType)lgst_err);//GST_MESSAGE_ANY;
  return {};
}

inline GstElement * StreamTraits<Video>::get_pipeline() const noexcept 
{
  return pipeline_.get(); 
}

inline std::expected<void, VideoErrorInfo>
StreamTraits<Video>::release() noexcept
{
  if (!pipeline_.get()){
    return err::unexpected(VideoError::PipelineError,"pipeline error occured while releasing resource");
  } 
  gst_element_set_state(pipeline_.get(),GST_STATE_NULL);
  return {};
}

}
