#pragma once

#include <cstdio>
#include <string>
#include <string_view>

namespace GE::utils
{

inline std::string read_file(std::string_view filePath)
{
    auto* file = std::fopen(filePath.data(), "rt");
    fseek(file, 0, SEEK_END);
    auto length = ftell(file);
    std::string content(length, ' ');
    fseek(file, 0, SEEK_SET);
    fread(&content[0], 1, length, file);
    fclose(file);

    return content;
}

}