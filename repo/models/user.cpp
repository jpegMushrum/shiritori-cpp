#include "user.hpp"

using ull = unsigned long long;

User::User() : id(0), nickname("") {}

User::User(ull id, std::string nickname) : id(id), nickname(nickname) {}