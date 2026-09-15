#include "thread_pool.hpp"

ThreadPool::ThreadPool(usize num_workers) {
    for (usize i{}; i < num_workers; ++i) {
        workers_.emplace_back(&ThreadPool::worker, this);
    }
}

ThreadPool::~ThreadPool() {
    {
        std::unique_lock lock{mutex_};
        stop_ = true;
    }

    condition_variable_.notify_all();
    for (std::thread& worker : workers_) {
        worker.join();
    }
}

void ThreadPool::worker() {
    for (;;) {
        std::function<void()> current_task{};
        {
            std::unique_lock lock{mutex_};
            condition_variable_.wait(lock, [this]() {
                return stop_ or !queue_.empty();
            });

            if (stop_ and queue_.empty()) {
                break;
            }

            if (queue_.empty()) {
                continue;
            }

            current_task = queue_.front();
            queue_.pop();
        }
        current_task();
    }
}
