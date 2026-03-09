#include "user.hpp"

using ull = unsigned long long;

User::User() : id(0), nickname(""), words_awg(0) {}

User::User(ull id, std::string nickname, double words_awg)
    : id(id), nickname(nickname), words_awg(words_awg)
{
}