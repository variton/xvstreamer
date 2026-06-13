
#ifndef ERROR_HDR_H
#define ERROR_HDR_H

#include <error_info.h>
#include <corety.h>
#include <string>

namespace core{

template <typename ErrorType, topology::HasCharMessage MsgType>
auto unexpected(ErrorType error, MsgType* msg) {
    std::string message = msg ? msg->message : "unknown error";
    return err::unexpected<ErrorType>(error, message);
}


}

#endif
