
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <doctest/doctest.h>

#include <env_mgr.h>

TEST_CASE("EnvMgr::get_env_var returns RC from test environment")
{
  auto & env = utils::EnvMgr::get_instance();

  auto rc = env.get_env_var("RC");

  REQUIRE(rc.has_value());
  CHECK(rc.value() == "/home/cxx-core/rc");
}

TEST_CASE("EnvMgr::get_env_var returns nullopt for missing variable")
{
  auto & env = utils::EnvMgr::get_instance();

  auto result = env.get_env_var("__ENV_MGR_TEST_MISSING_VAR__");

  CHECK(result == std::nullopt);
}

TEST_CASE("EnvMgr::get_envv returns RC from test environment")
{
  auto & env = utils::EnvMgr::get_instance();

  auto rc = env.get_envv("RC");

  REQUIRE(rc.has_value());
  CHECK(rc.value() == "/home/cxx-core/rc");
}

TEST_CASE("EnvMgr::get_envv returns error for missing variable")
{
  auto & env = utils::EnvMgr::get_instance();

  auto result = env.get_envv("__ENV_MGR_TEST_MISSING_VAR__");

  REQUIRE(!result.has_value());
  CHECK(result.error().message == "No env var found\n");
}
