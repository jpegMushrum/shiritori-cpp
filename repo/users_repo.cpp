#include "users_repo.hpp"
#include "user.hpp"

using ull = unsigned long long;

UsersRepo::UsersRepo() {

}

User UsersRepo::getUser(ull id) {
    User result(id);

    return result;
}