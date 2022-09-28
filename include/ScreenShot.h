//    This file is part of Examples repository by Pawe� Dybowski.
//
//    Copyright (C) 2020 Pawe� Dybowski <dybowski015 at gmail dot com>
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
// Created by pawel on 14.09.22.
//

#ifndef EXAMPLES_SCREENSHOT_H
#define EXAMPLES_SCREENSHOT_H

#include <chrono>

#include <opencv2/opencv.hpp>

struct ScreenShot {

    ScreenShot(cv::Mat image, std::chrono::system_clock::time_point timestamp) : image(image), timestamp(timestamp) {}

    cv::Mat image;
    std::chrono::system_clock::time_point timestamp;
};

#endif //EXAMPLES_SCREENSHOT_H