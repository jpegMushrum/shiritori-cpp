#include <gtest/gtest.h>

#include <cstdio>
#include <filesystem>
#include <fstream>

#include "game.hpp"
#include "games_repo.hpp"
#include "user.hpp"
#include "users_repo.hpp"

using ull = unsigned long long;

std::string createTempDatabase(const std::string& name)
{
    std::filesystem::path tempDir = std::filesystem::temp_directory_path();
    std::string dbPath = (tempDir / (name + ".db")).string();

    if (std::filesystem::exists(dbPath))
    {
        std::filesystem::remove(dbPath);
    }

    return dbPath;
}

void removeTempDatabase(const std::string& dbPath)
{
    if (std::filesystem::exists(dbPath))
    {
        std::filesystem::remove(dbPath);
    }

    if (std::filesystem::exists(dbPath + "-wal"))
    {
        std::filesystem::remove(dbPath + "-wal");
    }
    if (std::filesystem::exists(dbPath + "-shm"))
    {
        std::filesystem::remove(dbPath + "-shm");
    }
}

class UsersRepoTest : public ::testing::Test
{
  protected:
    void SetUp() override
    {
        dbPath = createTempDatabase("users_test");
        repo = std::make_unique<UsersRepo>(dbPath);
    }

    void TearDown() override
    {
        repo.reset();
        removeTempDatabase(dbPath);
    }

    std::string dbPath;
    std::unique_ptr<UsersRepo> repo;
};

TEST_F(UsersRepoTest, AddUserReturnsValidId)
{
    User user(0, "TestUser");

    ull userId = repo->addUser(user);

    EXPECT_GT(userId, 0);
}

TEST_F(UsersRepoTest, AddUserMultipleUsers)
{
    User user1(0, "User1");
    User user2(0, "User2");
    User user3(0, "User3");

    ull id1 = repo->addUser(user1);
    ull id2 = repo->addUser(user2);
    ull id3 = repo->addUser(user3);

    EXPECT_EQ(id1, 1);
    EXPECT_EQ(id2, 2);
    EXPECT_EQ(id3, 3);
}

TEST_F(UsersRepoTest, GetUserReturnsCorrectData)
{
    User originalUser(0, "Alice");
    ull userId = repo->addUser(originalUser);

    User retrievedUser = repo->getUser(userId);

    EXPECT_EQ(retrievedUser.id, userId);
    EXPECT_EQ(retrievedUser.nickname, "Alice");
}

TEST_F(UsersRepoTest, GetUserWithNonExistentId)
{
    User user = repo->getUser(9999);

    EXPECT_EQ(user.id, 0);
    EXPECT_EQ(user.nickname, "");
}

TEST_F(UsersRepoTest, AddUserWithDifferentNicknames)
{
    std::vector<std::string> nicknames = {"Alice", "Bob", "Charlie", "Diana", "Eve"};
    std::vector<ull> userIds;

    for (const auto& nickname : nicknames)
    {
        User user(0, nickname);
        userIds.push_back(repo->addUser(user));
    }

    for (size_t i = 0; i < nicknames.size(); ++i)
    {
        User retrieved = repo->getUser(userIds[i]);
        EXPECT_EQ(retrieved.nickname, nicknames[i]);
    }
}

TEST_F(UsersRepoTest, AddUserWithEmptyNickname)
{
    User user(0, "");

    ull userId = repo->addUser(user);

    User retrieved = repo->getUser(userId);
    EXPECT_EQ(retrieved.nickname, "");
}

TEST_F(UsersRepoTest, AddUserWithLongNickname)
{
    std::string longNickname(255, 'a');
    User user(0, longNickname);

    ull userId = repo->addUser(user);
    User retrieved = repo->getUser(userId);

    EXPECT_EQ(retrieved.nickname, longNickname);
}

TEST_F(UsersRepoTest, AddUserWithSpecialCharacters)
{
    User user(0, "User@#$%^&*()");

    ull userId = repo->addUser(user);
    User retrieved = repo->getUser(userId);

    EXPECT_EQ(retrieved.nickname, "User@#$%^&*()");
}

TEST_F(UsersRepoTest, AddUserWithUTF8Nickname)
{
    User user(0, "ユーザー");

    ull userId = repo->addUser(user);
    User retrieved = repo->getUser(userId);

    EXPECT_EQ(retrieved.nickname, "ユーザー");
}

TEST_F(UsersRepoTest, ChangeUserUpdatesNickname)
{
    User originalUser(0, "Original");
    ull userId = repo->addUser(originalUser);

    User modifiedUser(userId, "Modified");
    repo->changeUser(modifiedUser);

    User retrieved = repo->getUser(userId);
    EXPECT_EQ(retrieved.nickname, "Modified");
}

TEST_F(UsersRepoTest, ChangeUserUpdatesGamesAndWords)
{
    User originalUser(0, "TestUser");
    ull userId = repo->addUser(originalUser);

    User modifiedUser(userId, "TestUser");
    repo->changeUser(modifiedUser);

    User retrieved = repo->getUser(userId);
    EXPECT_EQ(retrieved.nickname, "TestUser");
}

TEST_F(UsersRepoTest, ChangeUserUpdatesAllFields)
{
    User originalUser(0, "Alice");
    ull userId = repo->addUser(originalUser);

    User modifiedUser(userId, "Bob");
    repo->changeUser(modifiedUser);

    User retrieved = repo->getUser(userId);
    EXPECT_EQ(retrieved.nickname, "Bob");
}

TEST_F(UsersRepoTest, ChangeUserMultipleTimes)
{
    User user(0, "Original");
    ull userId = repo->addUser(user);

    User update1(userId, "Update1");
    repo->changeUser(update1);

    User retrieved1 = repo->getUser(userId);
    EXPECT_EQ(retrieved1.nickname, "Update1");

    User update2(userId, "Update2");
    repo->changeUser(update2);

    User retrieved2 = repo->getUser(userId);
    EXPECT_EQ(retrieved2.nickname, "Update2");
}

TEST_F(UsersRepoTest, ChangeUserWithLargeNumbers)
{
    User originalUser(0, "TestUser");
    ull userId = repo->addUser(originalUser);

    User modifiedUser(userId, "TestUser");
    repo->changeUser(modifiedUser);

    User retrieved = repo->getUser(userId);
    EXPECT_EQ(retrieved.nickname, "TestUser");
}

class GamesRepoTest : public ::testing::Test
{
  protected:
    void SetUp() override
    {
        dbPath = createTempDatabase("games_test");
        repo = std::make_unique<GamesRepo>(dbPath);
    }

    void TearDown() override
    {
        repo.reset();
        removeTempDatabase(dbPath);
    }

    std::string dbPath;
    std::unique_ptr<GamesRepo> repo;
};

TEST_F(GamesRepoTest, PutGameStoreSingleGame)
{
    Game game(1, 100, 5, 1);
    std::vector<Game> games{game};

    EXPECT_NO_THROW(repo->putGame(games));
}

TEST_F(GamesRepoTest, PutGameStoreMultiplePlayersInOneGame)
{
    std::vector<Game> games{Game(1, 100, 10, 1), Game(1, 101, 8, 2), Game(1, 102, 6, 3)};

    EXPECT_NO_THROW(repo->putGame(games));
}

TEST_F(GamesRepoTest, PutGameThenGetGameHistory)
{
    std::vector<Game> originalGames{Game(1, 100, 10, 1), Game(1, 101, 8, 2)};

    repo->putGame(originalGames);

    auto gameHistory = repo->getGameHistoryByUserId(100);

    EXPECT_EQ(gameHistory.size(), 1);
    EXPECT_EQ(gameHistory[0].userId, 100);
    EXPECT_EQ(gameHistory[0].words, 10);
    EXPECT_EQ(gameHistory[0].place, 1);
}

TEST_F(GamesRepoTest, GetGameHistoryMultipleGames)
{
    std::vector<Game> game1{Game(1, 100, 10, 1), Game(1, 101, 5, 2)};

    std::vector<Game> game2{Game(2, 100, 8, 1), Game(2, 102, 6, 2)};

    repo->putGame(game1);
    repo->putGame(game2);

    auto history = repo->getGameHistoryByUserId(100);

    EXPECT_EQ(history.size(), 2);
}

TEST_F(GamesRepoTest, GetGameHistoryNonexistentUser)
{
    std::vector<Game> games{Game(1, 100, 10, 1)};
    repo->putGame(games);

    auto history = repo->getGameHistoryByUserId(9999);

    EXPECT_EQ(history.size(), 0);
}

TEST_F(GamesRepoTest, PutGameWithZeroWords)
{
    std::vector<Game> games{Game(1, 100, 0, 1)};

    EXPECT_NO_THROW(repo->putGame(games));
}

TEST_F(GamesRepoTest, PutGameWithDifferentPlaces)
{
    std::vector<Game> games{Game(1, 100, 10, 1), Game(1, 101, 8, 2), Game(1, 102, 6, 3),
                            Game(1, 103, 4, 4)};

    repo->putGame(games);

    auto history100 = repo->getGameHistoryByUserId(100);
    auto history101 = repo->getGameHistoryByUserId(101);
    auto history102 = repo->getGameHistoryByUserId(102);
    auto history103 = repo->getGameHistoryByUserId(103);

    EXPECT_EQ(history100[0].place, 1);
    EXPECT_EQ(history101[0].place, 2);
    EXPECT_EQ(history102[0].place, 3);
    EXPECT_EQ(history103[0].place, 4);
}

TEST_F(GamesRepoTest, PutGameMultipleTimes)
{
    std::vector<Game> batch1{Game(1, 100, 10, 1)};
    repo->putGame(batch1);

    std::vector<Game> batch2{Game(2, 100, 12, 1)};
    repo->putGame(batch2);

    auto history = repo->getGameHistoryByUserId(100);

    EXPECT_EQ(history.size(), 2);
    EXPECT_EQ(history[0].words, 10);
    EXPECT_EQ(history[1].words, 12);
}

TEST_F(GamesRepoTest, GetGameHistoryReturnsCorrectOrder)
{
    std::vector<Game> games{Game(1, 100, 15, 1)};
    repo->putGame(games);

    games = {Game(2, 100, 20, 1)};
    repo->putGame(games);

    auto history = repo->getGameHistoryByUserId(100);

    EXPECT_EQ(history[0].words, 15);
    EXPECT_EQ(history[1].words, 20);
}

TEST_F(GamesRepoTest, PutGameWithLargeWordCounts)
{
    std::vector<Game> games{Game(1, 100, 999999, 1)};

    repo->putGame(games);

    auto history = repo->getGameHistoryByUserId(100);
    EXPECT_EQ(history[0].words, 999999);
}

TEST_F(GamesRepoTest, PutGameMixedUserIds)
{
    std::vector<Game> games{Game(1, 1000, 10, 1), Game(1, 2000, 8, 2), Game(1, 3000, 6, 3)};

    repo->putGame(games);

    auto hist1 = repo->getGameHistoryByUserId(1000);
    auto hist2 = repo->getGameHistoryByUserId(2000);
    auto hist3 = repo->getGameHistoryByUserId(3000);

    EXPECT_EQ(hist1[0].userId, 1000);
    EXPECT_EQ(hist2[0].userId, 2000);
    EXPECT_EQ(hist3[0].userId, 3000);
}

TEST_F(GamesRepoTest, PutGameSinglePlayerGame)
{
    std::vector<Game> games{Game(1, 100, 20, 1)};

    repo->putGame(games);

    auto history = repo->getGameHistoryByUserId(100);
    EXPECT_EQ(history.size(), 1);
    EXPECT_EQ(history[0].place, 1);
}

TEST_F(GamesRepoTest, GetGameHistoryContainsGameId)
{
    std::vector<Game> games{Game(1, 100, 10, 1)};
    repo->putGame(games);

    auto history = repo->getGameHistoryByUserId(100);

    EXPECT_EQ(history[0].words, 10);
}

TEST_F(GamesRepoTest, PutGameEmptyVector)
{
    std::vector<Game> emptyGames;

    EXPECT_NO_THROW(repo->putGame(emptyGames));
}
