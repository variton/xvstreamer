
#ifndef VIDEO_H
#define VIDEO_H

/**
 * @file video.h
 * @brief Video stream type and GStreamer-backed stream specialization.
 */

#include <stream.h>
#include <expected>

#include <ncnm.h>
#include <error_info.h>
#include <gst_memory.h>

namespace xstream {

template <typename T>
using Default = core::NCNM<T>;

/**
 * @brief Tag type representing a video stream.
 */
class Video:public Default<Video>{};

/**
 * @brief Error codes returned by video stream operations.
 */
enum class VideoError
{
  /// Failed to create the GStreamer pipeline.
  PipelineInitFailed,
  /// Failed to create or retrieve the GStreamer bus.
  BusInitFailed,
  /// Generic pipeline operation failure.
  PipelineError,
  /// Unsupported or invalid video type.
  InvalidVideoType,
};

/**
 * @brief Error information type for video stream failures.
 */
using VideoErrorInfo = err::ErrorInfo<VideoError>;

/**
 * @brief GStreamer-backed stream implementation for video playback.
 */
template <>
struct Stream<Video>:public Default<Stream<Video>> {

  /**
   * @brief Constructs an empty video stream.
   */
  Stream() noexcept;

  /**
   * @brief Initializes the stream from a local video file path.
   * @param video_file_path Path to the local video file.
   * @param argc Optional argument count passed to GStreamer initialization.
   * @param argv Optional argument vector passed to GStreamer initialization.
   * @return Empty result on success, or video error information on failure.
   */
  std::expected<void,VideoErrorInfo> init(const std::string & video_file_path, int argc=0, char ** argv=nullptr) noexcept;

  /**
   * @brief Starts video playback.
   * @return Empty result on success, or video error information on failure.
   */
  std::expected<void,VideoErrorInfo> start() noexcept;

  /**
   * @brief Returns the underlying GStreamer pipeline.
   * @return Non-owning pointer to the pipeline, or nullptr when uninitialized.
   */
  GstElement * get_pipeline() const noexcept;

  /**
   * @brief Releases stream resources and stops the pipeline.
   * @return Empty result on success, or video error information on failure.
   */
  std::expected<void,VideoErrorInfo> release() noexcept;

private:
  xvscore::GstPtr<GstElement> pipeline_; 
  xvscore::GstPtr<GstBus> bus_;
  //core::GstPtr<GstMessage> message_; 
};

} //xstream

#include <video.tpp>

#endif
