#include <functional>
#include <memory>

#include "info_service.hpp"
#include "user_info.hpp"

using ull = unsigned long long;

InfoService::InfoService(std::shared_ptr<UsersRepo> usersRepo) : usersRepo_(usersRepo) {}

UserInfo InfoService::getUserInfo(ull id)
{
    auto user = usersRepo_->getUser(id);

    return UserInfo(user.id);
}
