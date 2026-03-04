#include <memory>
#include <functional>

#include "info_controller.hpp"
#include "task_queue.hpp"
#include "user_info.hpp"

using ull = unsigned long long;

InfoController::InfoController(std::shared_ptr<TaskQueue> queue, std::unique_ptr<InfoService> infoService):
    taskQueue_(queue),
    infoService_(std::move(infoService)) 
{}

void InfoController::getUserInfo(ull id, std::function<void(UserInfo)> f) {
    taskQueue_->addTask([this, id, f]() {
        auto user = infoService_->getUserInfo(id);
        f(user);
    });
}