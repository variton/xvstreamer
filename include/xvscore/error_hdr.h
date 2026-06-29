
#ifndef ERROR_HDR_H
#define ERROR_HDR_H

/**
 * @file error_hdr.h
 * @brief Helpers for constructing xvscore error results.
 */

#include <error_info.h>
#include <corety.h>
#include <string>

namespace xvscore{

/**
 * @brief Creates an unexpected error result with an optional message payload.
 * @tparam ErrorType Error value type.
 * @tparam MsgType Message object type satisfying topology::HasCharMessage.
 * @param error Error value to wrap.
 * @param msg Optional message object. When null, "unknown error" is used.
 * @return Unexpected error result produced by err::unexpected.
 */
template <typename ErrorType, topology::HasCharMessage MsgType>
auto unexpected(ErrorType error, MsgType* msg) {
    std::string message = msg ? msg->message : "unknown error";
    return err::unexpected<ErrorType>(error, message);
}


}

#endif
