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

#include "Thread.h"

#include <iostream>

dbs::Thread::Thread(unsigned long numberOfLoops, bool startImmediately, unsigned long timeoutInMilliseconds)
        : loop_count_(numberOfLoops), timeout_(timeoutInMilliseconds) {
    if (startImmediately) {
        Start();
    }
}

bool dbs::Thread::Start() {
    if (IsStarted()) {
        if (IsDone()) {
            StopAndWait();
        } else {
            return false;
        }
    }
    std::unique_lock<std::mutex> lock(mutex_);
    thread_ = new std::thread(&Thread::operator(), this);
    started_ = true;
    return true;
}

bool dbs::Thread::WaitUntilReady() {
    if (!IsStarted()) {
        return false;
    }
    while (!IsReady()) {
        Sleep();
    }
    return true;
}

bool dbs::Thread::Stop() {
    if (!IsStarted()) {
        return false;
    } else {
        std::unique_lock<std::mutex> lock(mutex_);
        return (stopRequested_ = true);
    }
}

bool dbs::Thread::StopAndWait() {
    if (!Stop()) {
        return false;
    } else {
        WaitUntilDone();
        CleanUp();
        return true;
    }
}

bool dbs::Thread::WaitUntilDone() {
    if (!IsStarted() || !IsStopRequested()) {
        return false;
    } else {
        while (!IsDone()) {
            Sleep();
        }
    }
}


void dbs::Thread::CleanUp() {
    std::unique_lock<std::mutex> lock(mutex_);
    thread_->join();
    delete thread_;
    started_ = false;
    stopRequested_ = false;
    pauseRequested_ = false;
    resumeRequested_ = false;
    ready_ = false;
    paused_ = false;
    done_ = false;
}

bool dbs::Thread::PauseAndWait() {
    if (!Pause()) {
        return false;
    } else {
        while (!IsPaused()) {
            Sleep();
        }
        return true;
    }
}

bool dbs::Thread::ResumeAndWait() {
    if (!Resume()) {
        return false;
    } else {
        while (IsPaused()) {
            Sleep();
        }
        return true;
    }
}

void dbs::Thread::operator()() {
    Init();
    SetReady();
    unsigned int loops_done = 0;
    while (!IsStopRequested() && (loop_count_ == 0 || loops_done < loop_count_)) {
        if (IsPaused()) {
            if (IsResumeRequested()) {
                std::unique_lock<std::mutex> lock(mutex_);
                paused_ = false;
                resumeRequested_ = false;
            }
        } else {
            if (IsPauseRequested()) {
                std::unique_lock<std::mutex> lock(mutex_);
                paused_ = true;
                pauseRequested_ = false;
            } else {
                Loop();
                if (loop_count_ > 0) {
                    loops_done++;
                }
            }
        }
        Sleep(timeout_);
    }
    DeInit();
    SetDone();
}