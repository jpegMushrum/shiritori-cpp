#include "mapper.hpp"

UserInfo Mapper::UserToDto(User user)
{
    return UserInfo(user.id, user.nickname, user.games, user.words);
}

GameInfo Mapper::GameToDto(Game game)
{
    return GameInfo(game.gameId, game.userId, game.words, game.place);
}