//    Copyright 2025 Lucas Guimarães Fernandes
//
//    Licensed under the Apache License, Version 2.0 (the "License");
//    you may not use this file except in compliance with the License.
//    You may obtain a copy of the License at
//
//        http://www.apache.org/licenses/LICENSE-2.0
//
//    Unless required by applicable law or agreed to in writing, software
//    distributed under the License is distributed on an "AS IS" BASIS,
//    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//    See the License for the specific language governing permissions and
//    limitations under the License.

#include "core/utils.hpp"

namespace PurpleHole {

int DivFloor(int a, int b) {
    return (int)std::floor((float)a / (float)b);
}

int Div(int a, int b) {
    return (int)std::ceil((float)a / (float)b);
}

std::string GenID(std::string classType) {
    std::string classID = "";
    if (classType == "player") {
        classID = "01";
    } else {
        classID = "00";
    }

    std::string identifier = std::to_string(curr_id++);

    if (kIdSize-2-identifier.size() < 0)
        std::cerr << "[WARNING!] ID SIZE CANNOT COMPRISE THE NECESSARY NUMBER OF IDS\n";

    for (int i = 0; i < kIdSize-2-identifier.size(); i++) {
        classID += '0';
    }
    classID += identifier;

    return classID;
}

}  // namespace PurpleHole