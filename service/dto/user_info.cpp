#include <iostream>

#include "user_info.hpp"

using ull = unsigned long long;

UserInfo::UserInfo(ull id) : id(id) {}

std::ostream& operator<<(std::ostream& out, const UserInfo& ui)
{
    out << ui.id;
    return out;
}