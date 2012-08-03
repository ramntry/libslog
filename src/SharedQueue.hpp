/*
 * File:   SharedQueue.hpp
 * Author: Filinger
 *
 * Created on July 12, 2012, 12:21 PM
 */

#ifndef SHAREDQUEUE_HPP
#define SHAREDQUEUE_HPP

#include <queue>
#include <mutex>
#include <condition_variable>

namespace slog
{

template <typename T> class SharedQueue
{
public:
    SharedQueue() { };
    virtual ~SharedQueue() { };
    inline void push(const T& pushed_item)
    {
        std::lock_guard<std::mutex> guard(mutex_);
        queue_.push(pushed_item);
        data_cond_.notify_one();
    }
    inline bool pop(T& popped_item)
    {
        if (queue_.empty()) return false;
        std::lock_guard<std::mutex> guard(mutex_);
        popped_item = queue_.front();
        queue_.pop();
        return true;
    }
    inline bool empty() const
    {
        return queue_.empty();
    }
    inline signed int size() const
    {
        return queue_.size();
    }
    void WaitForPop(T& popped_item)
    {
        std::unique_lock<std::mutex> guard(mutex_);
        while (queue_.empty())
        {
            data_cond_.wait(guard);
        }
        popped_item = queue_.front();
        queue_.pop();
    }

private:
    std::queue<T> queue_;
    mutable std::mutex mutex_;
    std::condition_variable data_cond_;

    SharedQueue(const SharedQueue&);
    void operator=(const SharedQueue&);
};

} //End namespace slog

#endif	/* SHAREDQUEUE_HPP */
