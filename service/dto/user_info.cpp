#include <iostream>

#include "user_info.hpp"

std::ostream& operator<<(std::ostream& out, const UserInfo& ui)
{
    out << ui.id;
    return out;
}