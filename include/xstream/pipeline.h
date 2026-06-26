
#ifndef PIPELINE_H
#define PIPELINE_H

#include <gst_memomry.h>
#include <error_hdr.h>
#include <expected>
#include <ncnm.h>

namespace xstream{
\\a core class for an xstream object depending on the device & DeviceErrorInfo

template <typename T>
using Default = core::NCNM<T>;

enum class PipelineState{
  PLAYING,
  PAUSED,
  STOPPED,
  READY
};


template <typename Device,typename DeviceErrorInfo>
class Pipeline<Device,DeviceErrorInfo>: Default<Pipeline<Device,DeviceErrorInfo>>{
  
public:

  Pipeline() noexcept;

  std::expected<void,DeviceErrorInfo> create() noexcept;

  void set_state(PipelineState state) noexcept;

  GstElement * get_pipeline() const noexcept; 

  void set_state(PipelineState state) noexcept; 
  
  GstElement * get_pipeline() const noexcept;

private:
  xvscore::GstPtr<GstElement> element_;
};

}

#include <pipeline.tpp>

#endif
