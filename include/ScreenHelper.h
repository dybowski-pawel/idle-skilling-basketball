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

#ifndef IDLE_SKILLING_BASKETBALL_SCREENHELPER_H
#define IDLE_SKILLING_BASKETBALL_SCREENHELPER_H

#include <Windows.h>
#include <opencv2/opencv.hpp>

#include "ScreenShot.h"

class ScreenHelper {
public:

    ScreenHelper();

    ~ScreenHelper();

    ScreenShot CaptureWholeScreen();

    ScreenShot CaptureScreen(cv::Point2i from, cv::Point2i to);

private:

    cv::Size GetScreenSize();

    static BITMAPINFOHEADER createBitmapHeader(cv::Size size);

    HWND hwnd;
    HDC hwindowDC;
    HDC hwindowCompatibleDC;
};


#endif //IDLE_SKILLING_BASKETBALL_SCREENHELPER_H
