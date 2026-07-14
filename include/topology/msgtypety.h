
#ifndef MSGTYPETY_H
#define MSGTYPETY_H

/**
 * @file msgtypety.h
 * @brief Core topology type concepts.
 */

#include <concepts>

namespace topology {

/**
 * @brief Concept for types exposing a C-string message member.
 *
 * A type satisfies this concept when `t.message` is convertible to
 * `const char*`.
 *
 * @tparam T Type to evaluate.
 */
template <typename T>
concept HasCharMessage = requires(T t) {
    { t.message } -> std::convertible_to<const char*>;
};    

}    

#endif
