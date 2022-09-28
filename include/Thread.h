//    This file is part of Examples repository by Paweł Dybowski.
//
//    Copyright (C) 2020 Paweł Dybowski <dybowski015 at gmail dot com>
//    https://github.com/dybowski-pawel/coding-examples
//
//    Examples is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    Examples is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with Examples.  If not, see <https://www.gnu.org/licenses/>.

//
// Created by pawel on 02.09.20.
//

#ifndef EXAMPLES_THREAD_H
#define EXAMPLES_THREAD_H

#include <atomic>
#include <thread>
#include <mutex>

namespace dbs {

/*******************************************************************************
 * This is a base Class for creating a thread<br>
 * You have to derive from it and override Init, Loop and DeInit methods
 ******************************************************************************/
    class Thread {
    public:

        /*******************************************************************************
         * Constructor of Thread class
         *
         * @param numberOfLoops How many times should loop be executed. 0 means infinite
         * @param timeoutInMilliseconds How long to wait between each loop execution. 0 means no wait
         * @param startImmediately Should thread be started immediately on creation
         * It is worth to have at least some timeout to not kill the processor
         ******************************************************************************/
        explicit Thread(unsigned long numberOfLoops = 0, bool startImmediately = false,
                        unsigned long timeoutInMilliseconds = 10);

        /*******************************************************************************
         * Destructor of Thread class
         ******************************************************************************/
         ~Thread();

        /*******************************************************************************
         * Start new thread if none is already running
         * If thread is already running, false will be returned
         *
         * @return If new thread was started
         ******************************************************************************/
        bool Start();

        /*******************************************************************************
         * Wait until thread finishes it's init method
         * If thread is not running, false will be returned
         *
         * @return If thread is running
         ******************************************************************************/
        bool WaitUntilReady();

        /*******************************************************************************
         * Request thread to stop
         * This will not wait for thread to actually stop
         * CleanUp will not be called and you'll have to do it manually
         * If thread is not running, false will be returned
         *
         * @return if new stop request was made
         ******************************************************************************/
        bool Stop();

        /*******************************************************************************
         * Stop and wait for thread to finish if running
         * CleanUp is called afterwards
         * If thread is not running, false will be returned
         *
         * @return If thread was fully stopped
         ******************************************************************************/
        bool StopAndWait();

        /*******************************************************************************
         * Wait until thread fully stops
         * If thread is not running, false will be returned
         * If thread was not scheduled for stop, false will be returned
         *
         * @return If thread was fully stopped
         ******************************************************************************/
        bool WaitUntilDone();

        /*******************************************************************************
         * Join thread and cleanup it's resources
         * If thread was not set to stop this will wait forever
         ******************************************************************************/
        void CleanUp();

        /*******************************************************************************
         * Request thread to pause
         * If thread is not running, false will be returned
         *
         * @return if new pause request was made
         ******************************************************************************/
        inline bool Pause() {
            std::unique_lock<std::mutex> lock(mutex_);
            return pauseRequested_ ? false : (pauseRequested_ = true);
        }

        /*******************************************************************************
         * Pause and wait for thread to finish loop
         * If thread is not running, false will be returned
         *
         * @return If thread was fully paused
         ******************************************************************************/
        bool PauseAndWait();

        /*******************************************************************************
         * Request thread to resume
         * If thread is not running, false will be returned
         *
         * @return if new resume request was made
         ******************************************************************************/
        inline bool Resume() {
            std::unique_lock<std::mutex> lock(mutex_);
            return resumeRequested_ ? false : (resumeRequested_ = true);
        }

        /*******************************************************************************
         * Resume and wait for thread to start loop
         * If thread is not running, false will be returned
         *
         * @return If thread was fully resumed
         ******************************************************************************/
        bool ResumeAndWait();

        /*******************************************************************************
         * Check if thread is paused
         *
         * @return is paused
         ******************************************************************************/
        inline bool IsStarted() {
            std::unique_lock<std::mutex> lock(mutex_);
            return started_;
        }

        /*******************************************************************************
         * Check if thread has initialized
         *
         * @return is ready
         ******************************************************************************/
        inline bool IsReady() {
            std::unique_lock<std::mutex> lock(mutex_);
            return ready_;
        }

        /*******************************************************************************
         * Check if thread is paused
         *
         * @return is paused
         ******************************************************************************/
        inline bool IsPaused() {
            std::unique_lock<std::mutex> lock(mutex_);
            return paused_;
        }

        /*******************************************************************************
         * Check if thread has scheduled to pause
         *
         * @return is thread scheduled for pause
         ******************************************************************************/
        inline bool IsPauseRequested() {
            std::unique_lock<std::mutex> lock(mutex_);
            return pauseRequested_;
        }

        /*******************************************************************************
         * Check if thread has scheduled to resume
         *
         * @return is thread scheduled for resume
         ******************************************************************************/
        inline bool IsResumeRequested() {
            std::unique_lock<std::mutex> lock(mutex_);
            return resumeRequested_;
        }

        /*******************************************************************************
         * Check if thread has scheduled to stop
         *
         * @return is thread scheduled for stop
         ******************************************************************************/
        inline bool IsStopRequested() {
            std::unique_lock<std::mutex> lock(mutex_);
            return stopRequested_;
        }

        /*******************************************************************************
         * Check if thread finished working
         *
         * @return is done
         ******************************************************************************/
        inline bool IsDone() {
            std::unique_lock<std::mutex> lock(mutex_);
            return done_;
        }

        /*******************************************************************************
         * Freeze calling thread for specified time
         *
         * @param timeoutInMilliseconds For how long should the thread be frozen. In milliseconds.
         * Default sleep is 10 milliseconds
         ******************************************************************************/
        inline static void Sleep(const unsigned long &timeoutInMilliseconds = 10) {
            std::this_thread::sleep_for(std::chrono::milliseconds(timeoutInMilliseconds));
        };

    protected:

        /*******************************************************************************
         * Method that will be called before loop starts
         * If you need to set/clean some variables on each start - that's a good place to do it
         *
         * @overload It must be overloaded to work
         ******************************************************************************/
        virtual void Init() {};

        /*******************************************************************************
         * Method that will be happening in a loop
         * When it finished one execution it waits for timeoutInMilliseconds and executes again
         *
         * @overload It must be overloaded to work
         ******************************************************************************/
        virtual void Loop() {};

        /*******************************************************************************
         * Method that will be called after loop ends
         * If you need to clean some variables on each end - that's a good place to do it
         *
         * @overload It must be overloaded to work
         ******************************************************************************/
        virtual void DeInit() {};

    private:

        /*******************************************************************************
         * Main methods that will be used for threading
         ******************************************************************************/
        void operator()();

        /*******************************************************************************
         * Sets ready status to true
         ******************************************************************************/
        inline void SetReady() {
            std::unique_lock<std::mutex> lock(mutex_);
            ready_ = true;
        }

        /*******************************************************************************
         * Sets paused state
         ******************************************************************************/
        inline void SetPaused() {
            std::unique_lock<std::mutex> lock(mutex_);
            paused_ = true;
            pauseRequested_ = false;
        }

        /*******************************************************************************
         * Sets resumed state
         ******************************************************************************/
        inline void SetResumed() {
            std::unique_lock<std::mutex> lock(mutex_);
            paused_ = false;
            resumeRequested_ = false;
        }

        /*******************************************************************************
         * Sets done status to true
         ******************************************************************************/
        inline void SetDone() {
            std::unique_lock<std::mutex> lock(mutex_);
            done_ = true;
        }

        std::atomic_bool started_{false};
        std::atomic_bool stopRequested_{false};
        std::atomic_bool pauseRequested_{false};
        std::atomic_bool resumeRequested_{false};
        std::atomic_bool ready_{false};
        std::atomic_bool paused_{false};
        std::atomic_bool done_{false};

        std::atomic_ulong timeout_;
        std::atomic_ulong loop_count_;

        std::mutex mutex_;
        std::unique_ptr<std::thread> thread_{nullptr};

    };

}


#endif //EXAMPLES_THREAD_H
