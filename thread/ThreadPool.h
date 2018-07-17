#pragma once

#include <vector>
#include <queue>
#include <functional>
#include <thread>
#include <condition_variable>
#include <atomic>
#include <mutex>

class ThreadPool
{
public:
    ThreadPool(int _threadnum);
    ~ThreadPool();

    void init();
    void commit(std::function<void()> _task);

private:
    bool stopped;
    int threadnum;
    std::vector<std::thread*> threads;
    std::mutex tasks_lock;
    std::condition_variable cv_task;
    std::queue<std::function<void()> > tasks;
};
