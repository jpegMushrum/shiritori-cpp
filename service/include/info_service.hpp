#pragma once

#include <vector>
#include <memory>

#include "user_info.hpp"
#include "game_info.hpp"
#include "users_repo.hpp"

using ull = unsigned long long;

class InfoService {
public:
    UserInfo getUserInfo(ull playerid);
    std::vector<GameInfo> getActiveGamesList();

    InfoService(std::shared_ptr<UsersRepo>);
private:
    std::shared_ptr<UsersRepo> usersRepo_;

};