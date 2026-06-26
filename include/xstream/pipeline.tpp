
#ifndef PIPELINE_H
#define PIPELINE_H

#include <gst_memomry.h>
#include <error_hdr.h>
#include <expected>
#include <ncnm.h>

namespace xstream{
\\this will be a core object an xstream object depending on the device

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

  void set_state(PipelineState state) const noexcept;
// std::expected<void,DeviceErrorInfo> create() noexcept;{
//   Device device{};
//   Gerror * raw_error{nullptr};
//   element_ = device.create_pipeline(pipeline_description, &raw_error);

//   return {};
// }




void set_state(PipelineState state) const noexcept {
  
  switch (state){
    case PipelineState::PLAYING:
      gst_element_set_state(element_.get(),GST_STATE_PLAYING);
      break;
    case PipelineState::PAUSED:
      gst_element_set_state(element_.get(),GST_STATE_PAUSED);
      break;
    case PipelineState::STOPPED:
      gst_element_set_state(element_.get(),GST_STATE_NULL);
      break;
    case PipelineState::READY:
      gst_element_set_state(element_.get(),GST_STATE_READY);
      break;
    default:
      break;
  }
}



  GstElement * get_pipeline() const noexcept { return element_.get();}

private:
  xvscore::GstPtr<GstElement> element_;
};

}
#endif
