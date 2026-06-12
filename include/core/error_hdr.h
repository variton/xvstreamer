
#ifndef ERROR_HDR_H
#define ERROR_HDR_H

#include <gst/gst.h>
#include <errty.h>
#include <error_info.h>

#include <string>

namespace core{

template <typename ErrorType>
auto unexpected(ErrorType error, GError * msg) {
  std::string message = msg? msg->message : "unknown error";
  return err::unexpected<ErrorType>(error,message);
}

}

#endif
