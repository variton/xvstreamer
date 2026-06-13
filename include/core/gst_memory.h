
#ifndef GST_MEMORY_H
#define GST_MEMORY_H

#include <memory>
#include <gst/gst.h>

namespace core {


template <typename T>
struct GstTraits;

template <>
struct GstTraits<GstElement> {
    static void release(GstElement* p) { gst_object_unref(p); }
};

template <>
struct GstTraits<GstPad> {
    static void release(GstPad* p) { gst_object_unref(p); }
};

template <>
struct GstTraits<GstBus> {
    static void release(GstBus* p) { gst_object_unref(p); }
};

template <>
struct GstTraits<GstCaps> {
    static void release(GstCaps* p) { gst_caps_unref(p); }
};

template <>
struct GstTraits<GError> {
    static void release(GError* p) { g_error_free(p); }
};

template <typename T>
struct GstDeleter {
    void operator()(T* p) const noexcept {
        if (p) {
            GstTraits<T>::release(p);
        }
    }
};

template <typename T>
using GstPtr = std::unique_ptr<T, GstDeleter<T>>;


} //core

#endif 
