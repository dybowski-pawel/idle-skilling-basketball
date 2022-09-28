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

#include "ImageHelper.h"

ImageHelper::ImageHelper() : board(LoadImage("board")), exit(LoadImage("exit")), lava(LoadImage("lava")), logo(
        LoadImage("logo")) {}

std::pair<cv::Point, cv::Point> ImageHelper::FindGameWindow(const cv::Mat& source) {
    return {FindImageInImage(source, logo), FindImageInImage(source, exit)};
}

cv::Point ImageHelper::FindLavaFigure(const cv::Mat& source) {
    return FindImageInImage(source, lava);
}

cv::Point ImageHelper::FindBall(const cv::Mat& source) {
    //todo:: Needs to be implemented
    return {};
}

cv::Point ImageHelper::FindBoard(const cv::Mat& source) {
    return FindImageInImage(source, board);
}

void ImageHelper::SaveImage(const cv::Mat& source, const std::string& path) {
    cv::imwrite(path, source);
}

cv::Point ImageHelper::FindImageInImage(const cv::Mat& source, const cv::Mat& imageToFind) {
    cv::Mat result = cv::Mat::eye(1, 1, CV_32F);
    cv::matchTemplate(source, imageToFind, result, cv::TM_CCOEFF_NORMED);
    double minVal, maxVal;
    cv::Point minPoint, maxPoint;
    cv::minMaxLoc(result, &minVal, &maxVal, &minPoint, &maxPoint);

    return maxPoint;
}

cv::Mat ImageHelper::LoadImage(const std::string & name) {
    return cv::imread(std::string(GetDataPath() + "/" + name), cv::IMREAD_COLOR);
}

std::string ImageHelper::GetDataPath() {
    return std::move(std::string({PROJECT_SOURCE_DIR, "/data"}));
}