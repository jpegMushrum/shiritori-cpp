#pragma once

#include <memory>
#include <vector>

#include "game_info.hpp"
#include "games_repo.hpp"
#include "user_info.hpp"
#include "users_repo.hpp"

using ull = unsigned long long;

class InfoService
{
  public:
    UserInfo getUserInfo(ull playerid);

    InfoService(std::shared_ptr<UsersRepo>, std::shared_ptr<GamesRepo>);

  private:
    std::shared_ptr<UsersRepo> usersRepo_;
    std::shared_ptr<GamesRepo> gamesRepo_;
};