#include "FileIO.hh"

#include "utils/Logger.hh"
#include <fstream>

namespace GE::utils
{

std::string FileIO::readText(std::string_view filePath)
{
    std::ifstream file{filePath.data(), std::ios::in | std::ios::ate};
    if (file.is_open())
    {
        auto size = file.tellg();
        std::string content(size, 0);
        file.seekg(0, std::ios::beg);
        file.read(content.data(), size);
        return content;
    }
    // TODO: need proper error handling
    ENGINE_LOG_ERROR("Failed To open file: {0}", filePath.data());
    std::exit(1);
}

}