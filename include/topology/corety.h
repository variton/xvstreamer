
#ifndef CORETY_H
#define CORETY_H

#include <concepts>

namespace topology {

template <typename T>
concept HasCharMessage = requires(T t) {
    { t.message } -> std::convertible_to<const char*>;
};    

}    

#endif
