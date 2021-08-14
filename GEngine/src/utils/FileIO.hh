#pragma once

#include "common.hh"

#include <string>
#include <string_view>

namespace GE::utils
{
class GE_PUBLIC FileIO
{
public:
    static std::string readText(std::string_view filePath);
};
}