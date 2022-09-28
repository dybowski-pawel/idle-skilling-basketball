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

#ifndef IDLE_SKILLING_BASKETBALL_IMAGEHELPER_H
#define IDLE_SKILLING_BASKETBALL_IMAGEHELPER_H

#include <opencv2/opencv.hpp>

class ImageHelper {

public:
    ImageHelper();

    static void SaveImage(const cv::Mat& source, const std::string& path);

    std::pair<cv::Point, cv::Point> FindGameWindow(const cv::Mat& source);

    cv::Point FindLavaFigure(const cv::Mat& source);

    cv::Point FindBoard(const cv::Mat& source);

private:

    static cv::Point FindImageInImage(const cv::Mat& source, const cv::Mat& imageToFind);

    static cv::Mat LoadImage(const std::string & name);

    static std::string GetDataPath();

    const cv::Mat board;
    const cv::Mat exit;
    const cv::Mat lava;
    const cv::Mat logo;

};


#endif //IDLE_SKILLING_BASKETBALL_IMAGEHELPER_H
