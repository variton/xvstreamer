
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest/doctest.h>

#include <gst/gst.h>
#include <error_info.h>
#include <error_hdr.h>

enum class GRuntimeError{
  RuntimeError, 
};

TEST_CASE("test_err_hdr") {
  GError * gerror{nullptr};
  std::expected<void, err::ErrorInfo<GRuntimeError>> runtime = core::unexpected(GRuntimeError::RuntimeError,gerror);
  REQUIRE_FALSE(runtime.has_value());
  CHECK(runtime.error().type == GRuntimeError::RuntimeError);
  CHECK(runtime.error().message == "unknown error");
}
