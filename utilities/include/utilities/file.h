//
// Created by user on 5/26/25.
//

#ifndef CONSERVATION_UTILITIES_FILE_H
#define CONSERVATION_UTILITIES_FILE_H

#include <filesystem>
#include <string>

namespace csv
{
    [[nodiscard]] std::string readAll(const std::filesystem::path& filepath);
}

#endif //CONSERVATION_UTILITIES_FILE_H
