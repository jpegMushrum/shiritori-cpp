#pragma once

#include "user.hpp"

using ull = unsigned long long;

class UsersRepo {
public:
    UsersRepo();

    User getUser(ull id);
private:

};