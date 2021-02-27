#pragma once
#include <mutex>
#include <optional>
#include <queue>

// A threadsafe-queue.
//https://bitbucket.org/marco/samples/src/develop/src/queue.cpp
//explained in https://codetrips.com/2020/07/26/modern-c-writing-a-thread-safe-queue/

//and an alternate if you want the pop/deque to block on empty queue instead of handling it yourself
//https://stackoverflow.com/questions/15278343/c11-thread-safe-queue

class non_empty_queue : public std::exception {
    std::string what_;
public:
    explicit non_empty_queue(std::string msg) { what_ = std::move(msg); }
    const char* what() const noexcept override { return what_.c_str(); }
};

template<typename T>
class SafeQueue {
    std::queue<T> queue_;
    mutable std::mutex mutex_;

    // Moved out of public interface to prevent races between this
    // and pop().
    [[nodiscard]] bool empty() const {
        return queue_.empty();
    }

public:
    SafeQueue() = default;
    SafeQueue(const SafeQueue<T>&) = delete;
    SafeQueue& operator=(const SafeQueue<T>&) = delete;

    SafeQueue(SafeQueue<T>&& other) noexcept(false) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!empty()) {
            throw non_empty_queue("Moving into a non-empty queue");
        }
        queue_ = std::move(other.queue_);
    }

    virtual ~SafeQueue() noexcept(false) {
        std::lock_guard<std::mutex> lock(mutex_);
        if (!empty()) {
            throw non_empty_queue("Destroying a non-empty queue");
        }
    }

    [[nodiscard]] unsigned long size() const {
        std::lock_guard<std::mutex> lock(mutex_);
        return queue_.size();
    }

    std::optional<T> pop() {
        std::lock_guard<std::mutex> lock(mutex_);
        if (queue_.empty()) {
            return {};
        }
        T tmp = queue_.front();
        queue_.pop();
        return tmp;
    }

    void push(const T& item) {
        std::lock_guard<std::mutex> lock(mutex_);
        queue_.push(item);
    }
};