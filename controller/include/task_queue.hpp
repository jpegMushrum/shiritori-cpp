#pragma once

#include <queue>
#include <functional>
#include <memory>
#include <thread>
#include <condition_variable>
#include <mutex>

class TaskQueue{
public:
    TaskQueue(unsigned int);
    ~TaskQueue();
    void addTask(std::function<void()>);
private:
    void startWorkerLoop();

    std::condition_variable cv_;
    std::mutex mu_;
    bool stop_;

    std::vector<std::unique_ptr<std::thread>> workers_;
    std::queue<std::function<void()>> tasks_;
};