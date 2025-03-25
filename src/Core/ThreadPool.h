#pragma once

#include "../MCraft.h"

#include <condition_variable>
#include <thread>

class ThreadPool {

public:
  ThreadPool(size_t ammountOfThreads = (std::thread::hardware_concurrency() - 1));
  ~ThreadPool();

  void EnqueueJob(std::function<void()>jobToDo);

private:
  void threadLoop();

   bool should_terminate = false;  

  std::mutex queue_mutex;  // Prevents data races to the job queue
  std::condition_variable mutex_condition;

  std::vector<std::thread> workers;
  std::queue<std::function<void()>> jobs;
};