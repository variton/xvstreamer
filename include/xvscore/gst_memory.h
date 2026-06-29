
#ifndef GST_MEMORY_H
#define GST_MEMORY_H

/**
 * @file gst_memory.h
 * @brief RAII helpers for managing GStreamer and GLib reference-counted types.
 */

#include <memory>
#include <gst/gst.h>

namespace xvscore {

/**
 * @brief Type-specific release operation for GStreamer and GLib objects.
 * @tparam T Managed object type.
 */
template <typename T>
struct GstTraits;

/**
 * @brief Release trait for GstElement.
 */
template <>
struct GstTraits<GstElement> {
    static void release(GstElement* p) { gst_object_unref(p); }
};

/**
 * @brief Release trait for GstPad.
 */
template <>
struct GstTraits<GstPad> {
    static void release(GstPad* p) { gst_object_unref(p); }
};

/**
 * @brief Release trait for GstBus.
 */
template <>
struct GstTraits<GstBus> {
    static void release(GstBus* p) { gst_object_unref(p); }
};

/**
 * @brief Release trait for GstCaps.
 */
template <>
struct GstTraits<GstCaps> {
    static void release(GstCaps* p) { gst_caps_unref(p); }
};

/**
 * @brief Release trait for GError.
 */
template <>
struct GstTraits<GError> {
    static void release(GError* p) { g_error_free(p); }
};

/**
 * @brief std::unique_ptr deleter that dispatches to GstTraits.
 * @tparam T Managed object type.
 */
template <typename T>
struct GstDeleter {
    /**
     * @brief Releases the object if the pointer is not null.
     * @param p Object pointer to release.
     */
    void operator()(T* p) const noexcept {
        if (p) {
            GstTraits<T>::release(p);
        }
    }
};

/**
 * @brief Unique ownership pointer for GStreamer and GLib objects.
 * @tparam T Managed object type with a GstTraits specialization.
 */
template <typename T>
using GstPtr = std::unique_ptr<T, GstDeleter<T>>;


} // namespace xvscore

#endif 
