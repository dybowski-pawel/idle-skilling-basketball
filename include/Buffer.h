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

#ifndef EXAMPLES_BUFFER_H
#define EXAMPLES_BUFFER_H

#include <queue>
#include <mutex>
#include <memory>
#include <condition_variable>

namespace dbs {

/*******************************************************************************
 * Buffer base class.
 * Right after initialization you have a thread-safe buffer object ready.
 * You can add, get, clear items to/from it.
 * Best suited for communication between threads
 ******************************************************************************/
    template<typename Data>
    class Buffer {
    public:

        /*******************************************************************************
         * Add new item to buffer and inform one listener
         ******************************************************************************/
        void Add(const std::shared_ptr<Data> &data) {
            std::unique_lock<std::mutex> lock(mutex_);
            queue_.push(data);
            lock.unlock();
            conditionalVariable_.notify_one();
        }

        /*******************************************************************************
         * Create shared_ptr from item and add it to buffer and inform one listener
         ******************************************************************************/
        void Add(const Data &data) {
            std::unique_lock<std::mutex> lock(mutex_);
            const auto &item = std::make_shared<Data>(data);
            queue_.push(item);
            lock.unlock();
            conditionalVariable_.notify_one();
        }

        /*******************************************************************************
         * Get oldest item and remove it from buffer.
         *
         * @return Oldest item
         ******************************************************************************/
        std::shared_ptr<Data> Get() {
            std::unique_lock<std::mutex> lock(mutex_);
            while (queue_.empty()) {
                conditionalVariable_.wait(lock);
            }
            auto item = queue_.front();
            queue_.pop();
            return item;
        }

        /*******************************************************************************
         * Try to get oldest item and remove it from buffer
         * If timeout passes, nullptr is returned
         *
         * @return Oldest item or nullptr
         ******************************************************************************/
        std::shared_ptr<Data> GetOrWait(const unsigned int &timeoutInMilliseconds) {
            std::unique_lock<std::mutex> lock(mutex_);
            if (queue_.empty()) {
                const auto &status = conditionalVariable_.wait_for(lock,
                                                                   std::chrono::milliseconds(timeoutInMilliseconds));
                if (status == std::cv_status::timeout) {
                    return std::shared_ptr<Data>(nullptr);
                }
            }
            const auto &item = queue_.front();
            queue_.pop();
            return item;
        }

        /*******************************************************************************
         * Check if buffer is empty
         *
         * @return If buffer is empty
         ******************************************************************************/
        bool Empty() {
            std::unique_lock<std::mutex> lock(mutex_);
            return queue_.empty();
        }

        /*******************************************************************************
         * Clear buffer
         ******************************************************************************/
        void Clear() {
            std::unique_lock<std::mutex> lock(mutex_);
            if (!queue_.empty()) {
                std::queue<std::shared_ptr<Data>> empty;
                std::swap(queue_, empty);
            }
        }

        /*******************************************************************************
         * Get size of buffer
         *
         * @return Size of buffer
         ******************************************************************************/
        size_t Size() {
            std::unique_lock<std::mutex> lock(mutex_);
            return queue_.size();
        }

    private:

        std::queue<std::shared_ptr<Data>> queue_;
        std::mutex mutex_;
        std::condition_variable conditionalVariable_;

    };
}


#endif //EXAMPLES_BUFFER_H
