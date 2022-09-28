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

#include <chrono>

#include "ScreenHelper.h"

ScreenHelper::ScreenHelper() {

    hwnd = GetDesktopWindow();
    hwindowDC = GetDC(hwnd);
    hwindowCompatibleDC = CreateCompatibleDC(hwindowDC);
}

ScreenHelper::~ScreenHelper() {

    DeleteDC(hwindowCompatibleDC);
    ReleaseDC(hwnd, hwindowDC);
}

ScreenShot ScreenHelper::CaptureWholeScreen() {
    CaptureScreen({0,0}, GetScreenSize());
}

ScreenShot ScreenHelper::CaptureScreen(cv::Point2i startPoint, cv::Point2i endPoint) {
    cv::Mat out;

    // get handles to a device context (DC)
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

    return {out, std::chrono::system_clock::now()};
}

cv::Size ScreenHelper::GetScreenSize() {
    return { GetSystemMetrics(SM_CXVIRTUALSCREEN), GetSystemMetrics(SM_CYVIRTUALSCREEN) };
}

BITMAPINFOHEADER ScreenHelper::createBitmapHeader(cv::Size size) {
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