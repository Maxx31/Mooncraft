#include "ThreadPool.h"

ThreadPool::ThreadPool(size_t ammountOfThreads)
{
    for (int i = 0; i < ammountOfThreads; i++)
    {
        workers.push_back(std::thread(&ThreadPool::threadLoop, this));
    }
}

ThreadPool::~ThreadPool()
{
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        should_terminate = true;
    }
    mutex_condition.notify_all();
    for (std::thread &active_workers: workers)
    {
        active_workers.join();
    }
    workers.clear();
}

void ThreadPool::EnqueueJob(std::function<void()>jobToDo)
{
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        jobs.push(jobToDo);
    }
    mutex_condition.notify_one();
}

void ThreadPool::threadLoop()
{
    while (true)
    {
        std::function<void()> job;
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            mutex_condition.wait(lock, [this] { return !jobs.empty() || should_terminate; });

            if (should_terminate)
                return;

            job = jobs.front();
            jobs.pop();
        }
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
        }
        job();
    }
}
