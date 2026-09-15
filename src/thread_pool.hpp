#pragma once
#include <condition_variable>
#include <functional>
#include <future>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

#include "types.hpp"

class ThreadPool {
public:
    explicit ThreadPool(usize num_workers = std::thread::hardware_concurrency());
    ~ThreadPool();

    template <typename Fn, typename... Args>
    auto enqueue(Fn&& fn, Args&&... args) -> std::future<decltype(fn(args...))> {
        auto function{std::bind(std::forward<Fn>(fn), std::forward<Args>(args)...)};
        auto encapsulated_ptr{std::make_shared<std::packaged_task<decltype(fn(args...))()> >(function)};

        std::future<std::result_of_t<Fn(Args...)> > future_object{
            encapsulated_ptr->get_future()
        };

        {
            std::unique_lock lock{mutex_};
            queue_.emplace([encapsulated_ptr]() {
                (*encapsulated_ptr)();
            });
        }

        condition_variable_.notify_one();
        return future_object;
    }

    ThreadPool(ThreadPool&) = delete;
    ThreadPool(const ThreadPool&) = delete;
    ThreadPool& operator=(ThreadPool&&) = delete;
    ThreadPool& operator=(const ThreadPool&) = delete;

private:
    std::vector<std::thread> workers_{};
    std::mutex mutex_{};
    std::condition_variable condition_variable_{};
    std::queue<std::function<void()> > queue_{};
    bool stop_{};

    void worker();
};
