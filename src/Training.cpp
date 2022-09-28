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
// Created by dybas on 28.09.2022.
//

#include "Training.h"

cv::Point Training::nullPoint = cv::Point(0,0);

void Training::Training::Loop() {

    switch(trainingState_) {
        case State::FIND_GAME_WINDOW: {
            FindGameWindow();
            break;
        }
        case State::FIND_LAVA_FIGURE: {
            FindLavaFigure();
            break;
        }
        case State::FIND_BALL: {
            FindBall();
            break;
        }
        case State::SAVE_RESULT: {
            SaveResult();
            break;
        }
        case State::EXIT: {
            Stop();
            break;
        }
        default: {
            break;
        }
    }
}

void Training::FindGameWindow() {
    auto wholeScreen = screenHelper_.CaptureWholeScreen();
    auto pair = imageHelper_.FindGameWindow(wholeScreen.image);
    if(isNullPoint(pair.first) || isNullPoint(pair.second)) {
        trainingState_ = State::EXIT;
    } else {
        gameWindowStart_ = pair.first;
        gameWindowEnd_ = pair.second;
        trainingState_ = State::FIND_LAVA_FIGURE;
    }
}

void Training::FindLavaFigure() {
    auto capture = screenHelper_.CaptureScreen(gameWindowStart_, gameWindowEnd_);
    auto point = imageHelper_.FindLavaFigure(capture.image);
    if(isNullPoint(point)) {
        trainingState_ = State::EXIT;
    } else {
        lastLavaPosition_ = point;
        trainingState_ = State::FIND_BALL;
    }
}

void Training::FindBall() {
    auto capture = screenHelper_.CaptureScreen(gameWindowStart_, gameWindowEnd_);
    auto point = imageHelper_.FindBall(capture.image);
    if(isNullPoint(point)) {
        trainingState_ = State::EXIT;
    } else {
//todo:: what next
    }
}

void Training::SaveResult() {

}

bool Training::isNullPoint(const cv::Point & point) {
    return (point == nullPoint);
}