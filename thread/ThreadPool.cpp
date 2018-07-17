#include "ThreadPool.h"

ThreadPool::ThreadPool(int _threadnum)
{
    threadnum=_threadnum;
    stopped=false;
}

ThreadPool::~ThreadPool()
{
    {
        std::lock_guard<std::mutex> lock(tasks_lock);
        stopped=true;
    }
    cv_task.notify_all();
    for(std::thread *thr:threads)
    {
        if(thr->joinable())
            thr->join();
        delete thr;
    }
    threads.shrink_to_fit();
}

void ThreadPool::init()
{
    for(int i=0; i<threadnum; i++)
    {
        std::thread* thr=new std::thread([this]
        {
            while(true)
            {
                std::function<void()>
                tfunc;
                {
                    std::unique_lock<std::mutex> lock(tasks_lock);
                    cv_task.wait(lock,[this] {return (stopped|| !tasks.empty());});
                    if(tasks.empty()&&stopped)
                        return;
                    tfunc=tasks.front();
                    tasks.pop();
                }
                tfunc();

            }
        });
        threads.push_back(thr);
    }
}

void ThreadPool::commit(std::function<void()> _task)
{
    {
        std::lock_guard<std::mutex> lock(tasks_lock);
        tasks.push(_task);
        cv_task.notify_one();
    }
}
