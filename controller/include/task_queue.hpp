#pragma once

#include <condition_variable>
#include <functional>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>

class TaskQueue
{
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