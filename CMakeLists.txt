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


cmake_minimum_required(VERSION 3.15.2)

SET("project" idle-skilling-basketball)

project("${project}")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

SET(source_Files
        src/main.cpp
        src/Version.cpp
        )

include_directories(include)

add_executable("${project}"
        ${source_Files}
        )
        
target_link_libraries("${project}" ${OpenCV_LIBS} )

SET("OpenCV_DIR" "${PROJECT_SOURCE_DIR}/dependencies/OpenCV-4.5.4/build")

find_package(OpenCV REQUIRED)
include_directories( ${OpenCV_INCLUDE_DIRS} )

message(STATUS "OpenCV_DIR: ${OpenCV_DIR}")
message(STATUS "OpenCV_INCLUDE_DIRS: ${OpenCV_INCLUDE_DIRS}")
message(STATUS "OpenCV_LIBS: ${OpenCV_LIBS}")
