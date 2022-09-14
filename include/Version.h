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

#ifndef EXAMPLES_VERSION_H
#define EXAMPLES_VERSION_H

#include <string>

namespace dbs {

    class Version {
    public:

        Version() = delete;

        /*******************************************************************************
         * Get current code version
         *
         * @return Current version in format major.minor.patch+build
         ******************************************************************************/
        static std::string GetVersion();

        /*******************************************************************************
         * Calculate value of current code version.
         *
         * Obtained value can be used to determine which version of code is newer
         * This can be used in database migrations
         *
         * @return Value of version in format major*1.000.000 + minor*1.000 + patch
         ******************************************************************************/
        static int CalculateValue();

    private:
        static constexpr char *VERSION_MAJOR = (char *) "0";
        static constexpr char *VERSION_MINOR = (char *) "0";
        static constexpr char *VERSION_PATCH = (char *) "0";
        static constexpr char *VERSION_BUILD = (char *) "";
    };
}

#endif //EXAMPLES_VERSION_H
