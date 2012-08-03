/*
 * File:   ActiveInterface.hpp
 * Author: Filinger
 *
 * Created on July 11, 2012, 6:58 PM
 */

#ifndef ACTIVEINTERFACE_HPP
#define ACTIVEINTERFACE_HPP

#include <thread>
#include <functional>
#include <memory>

#include "SharedQueue.hpp"

namespace slog
{

typedef std::function<void() > Job;

class ActiveInterface
{
public:
    static std::unique_ptr<ActiveInterface> Create()
    {
        std::unique_ptr<ActiveInterface> new_ptr(new ActiveInterface());
        new_ptr->thread_ = std::thread(&ActiveInterface::Run, new_ptr.get());
        return new_ptr;
    }
    virtual ~ActiveInterface()
    {
        Job stop = std::bind(&ActiveInterface::Stop, this);
        Schedule(stop);
        thread_.detach();
    }
    inline void Schedule(Job job_to_schedule)
    {
        job_queue_.push(job_to_schedule);
    }

private:
    inline void Stop()
    {
        continue_work_ = false;
    }
    void Run()
    {
        while (continue_work_)
        {
            Job job_to_execute;
            job_queue_.WaitForPop(job_to_execute);
            job_to_execute();
        }
    }

    SharedQueue<Job> job_queue_;
    std::thread thread_;
    bool continue_work_;

    ActiveInterface() : continue_work_(true) { }
    ActiveInterface(const ActiveInterface&);
    void operator=(const ActiveInterface&);
};

} //End namespace slog

#endif	/* ACTIVEINTERFACE_HPP */
