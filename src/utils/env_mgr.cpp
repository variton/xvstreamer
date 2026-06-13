#include <env_mgr.h>

namespace utils 
{

EnvMgr &EnvMgr::get_instance() noexcept
{
  static EnvMgr instance;
  return instance;
}

std::optional<std::string> EnvMgr::get_env_var(const char *name)
{
  if (const char *rc = std::getenv(name)) {
    return std::string{rc};
  }
  return std::nullopt;
}

std::expected<std::string, EnvMgrErrorInfo> EnvMgr::get_envv(const char *name)
{
  if (const char *envvar = std::getenv(name)) {
    auto value = std::string{envvar};
    return value;
  }
  return err::unexpected(EnvMgrError::NoEnvVar, "No env var found\n");
}

} // namespace utils 
