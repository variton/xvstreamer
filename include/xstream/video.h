
#ifndef VIDEO_H
#define VIDEO_H

#include <stream.h>
#include <expected>

#include <ncnm.h>
#include <error_info.h>
#include <gst_memory.h>

namespace xstream {

template <typename T>
using Default = core::NCNM<T>;

class Video:public Default<Video>{};

enum class VideoError
{
  PipelineInitFailed,
  BusInitFailed,
  PipelineError,
  InvalidVideoType,
};

using VideoErrorInfo = err::ErrorInfo<VideoError>;

template <>
struct Stream<Video>:public Default<Stream<Video>> {

  Stream() noexcept;
  std::expected<void,VideoErrorInfo> init(const std::string & video_file_path, int argc=0, char ** argv=nullptr) noexcept;
  std::expected<void,VideoErrorInfo> start() noexcept;
  GstElement * get_pipeline() const noexcept;
  std::expected<void,VideoErrorInfo> release() noexcept;

private:
  xvscore::GstPtr<GstElement> pipeline_; 
  xvscore::GstPtr<GstBus> bus_;
  //core::GstPtr<GstMessage> message_; 
};

} //xstream

#include <video.tpp>

#endif
