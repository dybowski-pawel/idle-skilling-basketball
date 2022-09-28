//    This file is part of Examples repository by Pawe³ Dybowski.
//
//    Copyright (C) 2021 Pawe³ Dybowski <dybowski015 at gmail dot com>
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

#include <utility>

#include "Screenshot.h"

HWND ScreenShot::GetSystemDesktopWindow() {
    return std::move(GetDesktopWindow());
}

cv::Size ScreenShot::GetScreenSize() {
    return { GetSystemMetrics(SM_CXVIRTUALSCREEN), GetSystemMetrics(SM_CYVIRTUALSCREEN) };
}

cv::Mat ScreenShot::CaptureScreen(HWND hwnd, cv::Point2i startPoint, cv::Point2i endPoint) {
    cv::Mat out;

    // get handles to a device context (DC)
    HDC hwindowDC = GetDC(hwnd);
    HDC hwindowCompatibleDC = CreateCompatibleDC(hwindowDC);
    SetStretchBltMode(hwindowCompatibleDC, COLORONCOLOR);

    int height = endPoint.y - startPoint.y;
    int width = endPoint.x - startPoint.x;

    // create mat object
    out.create(height, width, CV_8UC4);

    // create a bitmap
    HBITMAP hbwindow = CreateCompatibleBitmap(hwindowDC, width, height);
    BITMAPINFOHEADER bi = createBitmapHeader({ width, height });

    // use the previously created device context with the bitmap
    SelectObject(hwindowCompatibleDC, hbwindow);

    // copy from the window device context to the bitmap device context
    StretchBlt(hwindowCompatibleDC, startPoint.x, startPoint.y, width, height, hwindowDC, endPoint.x, endPoint.y, width, height, SRCCOPY);  //change SRCCOPY to NOTSRCCOPY for wacky colors !
    GetDIBits(hwindowCompatibleDC, hbwindow, 0, height, out.data, (BITMAPINFO*)&bi, DIB_RGB_COLORS);            //copy from hwindowCompatibleDC to hbwindow

    // avoid memory leak
    DeleteObject(hbwindow);
    DeleteDC(hwindowCompatibleDC);
    ReleaseDC(hwnd, hwindowDC);

    return std::move(out);
}

cv::Point ScreenShot::FindImageInImage(cv::Mat source, std::string imageToFind) {

    auto image = cv::imread(std::string(GetDataPath() + "/" + imageToFind), cv::IMREAD_COLOR);
    cv::Mat result = cv::Mat::eye(1, 1, CV_32F);
    cv::matchTemplate(source, image, result, cv::TM_CCOEFF_NORMED);
    double minVal, maxVal;
    cv::Point minPoint, maxPoint;
    cv::minMaxLoc(result, &minVal, &maxVal, &minPoint, &maxPoint);

    return std::move(maxPoint);
}

void ScreenShot::SaveImage(cv::Mat source, std::string path) {
    cv::imwrite(path.c_str(), source);
}

std::string ScreenShot::GetDataPath() {
    return std::move(std::string({ PROJECT_SOURCE_DIR, "/data" }));
}

BITMAPINFOHEADER ScreenShot::createBitmapHeader(cv::Size size) {
    BITMAPINFOHEADER  bi;

    // create a bitmap
    bi.biSize = sizeof(BITMAPINFOHEADER);
    bi.biWidth = size.width;
    bi.biHeight = -size.height;  //this is the line that makes it draw upside down or not
    bi.biPlanes = 1;
    bi.biBitCount = 32;
    bi.biCompression = BI_RGB;
    bi.biSizeImage = 0;
    bi.biXPelsPerMeter = 0;
    bi.biYPelsPerMeter = 0;
    bi.biClrUsed = 0;
    bi.biClrImportant = 0;

    return bi;
}









