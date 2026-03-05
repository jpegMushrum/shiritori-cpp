#include <functional>
#include <memory>
#include <vector>

#include "info_service.hpp"
#include "mapper.hpp"
#include "user_info.hpp"

using ull = unsigned long long;

InfoService::InfoService(std::shared_ptr<UsersRepo> usersRepo, std::shared_ptr<GamesRepo> gamesRepo)
    : usersRepo_(usersRepo), gamesRepo_(gamesRepo)
{
}

UserInfo InfoService::getUserInfo(ull id)
{
    auto user = usersRepo_->getUser(id);

    return Mapper::UserToDto(user);
}

std::vector<GameInfo> InfoService::getActiveGamesList()
{
    auto games = gamesRepo_->getActiveGames();
    std::vector<GameInfo> result(games.size());

    int i = 0;
    for (auto g : games)
    {
        result[i] = Mapper::GameToDto(g);
        i++;
    }

    return result;
}
