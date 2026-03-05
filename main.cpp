#include <functional>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "info_controller.hpp"
#include "info_service.hpp"
#include "task_queue.hpp"
#include "user_info.hpp"
#include "users_repo.hpp"

using ull = unsigned long long;

int main()
{
    auto usersRepo = std::make_shared<UsersRepo>();
    auto infoService = std::make_unique<InfoService>(usersRepo);

    auto taskQueue = std::make_shared<TaskQueue>(std::thread::hardware_concurrency());
    InfoController infoCtr(taskQueue, std::move(infoService));

    while (true)
    {
        std::string in;
        std::getline(std::cin, in);

        std::stringstream ss(in);
        std::string command;
        std::getline(ss, command, ' ');

        std::vector<std::string> args;
        std::string t;
        while (std::getline(ss, t, ' '))
        {
            args.push_back(t);
        }

        if (command == "getUser")
        {
            try
            {
                ull id = std::stoull(args[0]);

                infoCtr.getUserInfo(id, [](UserInfo ui) { std::cout << ui << '\n'; });
            }
            catch (...)
            {
                std::cerr << "getUser err: bad args";
            }

            continue;
        }

        std::cerr << "main err: Unknown command\n";
    }
}