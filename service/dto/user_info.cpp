#include <iostream>

#include "user_info.hpp"

using ull = unsigned long long;

UserInfo::UserInfo(ull id, std::string nickname, double words_awg)
    : id(id), nickname(nickname), words_awg(words_awg)
{
}

std::ostream& operator<<(std::ostream& out, const UserInfo& ui)
{
    out << ui.id << " " << ui.nickname << " " << ui.words_awg;

    return out;
}