#pragma once

#include <functional>

#include "task_queue.hpp"
#include "info_service.hpp"
#include "user_info.hpp"

using ull = unsigned long long;

class InfoController {
public:
    InfoController(std::shared_ptr<TaskQueue>, std::unique_ptr<InfoService>);

    void getUserInfo(ull id, std::function<void(UserInfo)>);
private:
    std::shared_ptr<TaskQueue> taskQueue_;
    std::unique_ptr<InfoService> infoService_;
};