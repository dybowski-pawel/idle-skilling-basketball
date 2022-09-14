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
// Created by pawel on 17.03.20.
//

#include "Version.h"

std::string dbs::Version::GetVersion() {
    std::string out;
    out.append(VERSION_MAJOR).append(".");
    out.append(VERSION_MINOR).append(".");
    out.append(VERSION_PATCH);

    if (!std::string(VERSION_BUILD).empty()) {
        out.append("+").append(VERSION_BUILD);
    }
    return out;
}

int dbs::Version::CalculateValue() {
    int value = 0;
    value += std::stoi(VERSION_MAJOR) * 1000 * 1000;
    value += std::stoi(VERSION_MINOR) * 1000;
    value += std::stoi(VERSION_PATCH);
    return value;
}
