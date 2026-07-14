#ifndef ENV_MGR_H
#define ENV_MGR_H

#include <optional>
#include <string>
#include <ncnm.h>
#include <err_utils.h>

namespace utils 
{

template <typename T>
using Default = core::NCNM<T>;

enum class EnvMgrError
{
  NoEnvVar,
  InvalidEnvVarType,
};

ERR_DEFINE_ERROR_INFO(EnvMgrError, EnvMgrErrorInfo);

class EnvMgr : public Default<EnvMgr>
{
public:
  static EnvMgr &get_instance() noexcept;

  std::optional<std::string> get_env_var(const char *name);

  std::expected<std::string, EnvMgrErrorInfo> get_envv(const char *name);

private:
  EnvMgr() = default;
};

} // namespace utils 

#endif
