#    This file is part of Examples repository by Pawe³ Dybowski.
#
#    Copyright (C) 2020 Pawe³ Dybowski <dybowski015 at gmail dot com>
#    https://github.com/dybowski-pawel/coding-examples
#
#    Examples is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    Examples is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with Examples.  If not, see <https://www.gnu.org/licenses/>.

#
# Created by pawel on 14.09.22.
#

SET("project" idle-skilling-basketball)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
cmake_minimum_required(VERSION 3.15.2)

project("${project}")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

add_definitions(-DPROJECT_SOURCE_DIR="${PROJECT_SOURCE_DIR}")

SET("OpenCV_BASE_DIR" "${PROJECT_SOURCE_DIR}/../../OpenCV-4.6.0")
SET("OpenCV_DIR" "${OpenCV_BASE_DIR}/mingw-build")
SET("OpenCV_SRC_DIR" "${OpenCV_BASE_DIR}/sources")
SET("OpenCV_INCLUDE_DIR" "${OpenCV_SRC_DIR}/include")

find_package(OpenCV REQUIRED)

SET(source_Files
        src/main.cpp
        src/Version.cpp
        src/ScreenShot.cpp
        src/ImageHelper.cpp
        src/ScreenHelper.cpp)

SET(include_Files
        include
        ${OpenCV_INCLUDE_DIRS}
        )

SET(link_Libraries
        ${OpenCV_LIBS}
        )

include_directories(${include_Files})

add_executable("${project}" ${source_Files})

target_link_libraries("${project}" ${link_Libraries})

message(STATUS "PROJECT_SOURCE_DIR: ${PROJECT_SOURCE_DIR}")
message(STATUS "OpenCV_DIR: ${OpenCV_DIR}")
message(STATUS "OpenCV_SRC_DIR: ${OpenCV_SRC_DIR}")
message(STATUS "OpenCV_INCLUDE_DIR: ${OpenCV_INCLUDE_DIR}")
message(STATUS "OpenCV_LIBS: ${OpenCV_LIBS}")
