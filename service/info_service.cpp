#include <memory>

#include "info_service.hpp"
#include "user_info.hpp"

using ull = unsigned long long;

InfoService::InfoService(std::shared_ptr<UsersRepo> usersRepo):
    usersRepo_(usersRepo)
{}

UserInfo InfoService::getUserInfo(ull id) { 
    UserInfo ui;
    ui.id = id;

    return ui;
}
