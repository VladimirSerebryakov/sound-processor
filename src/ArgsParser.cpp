#include "ArgsParser.h"

#include <cstring>
ArgsParser::ArgsParser(): _inFileName(nullptr), _outFileName(nullptr) {}
ArgsParser::~ArgsParser() = default;
ArgsParser::Result ArgsParser::parse(int argc, char* argv[])
{
    if(argc <= 1)
        return Result::noArgs;

    int i = 1;
    while(i < argc)
    {
        if(std::strcmp(argv[i], "--help") == 0 ||
           std::strcmp(argv[i], "-h") == 0)
        {
            return Result::noArgs;
        }
        if(std::strcmp(argv[i], "-i") == 0)
        {
            if(argc <= i + 1)
                return Result::badArgs;
            i++;
            _inFileName = argv[i];
            i++;
        }
        else if(std::strcmp(argv[i], "-o") == 0)
        {
            if(argc <= i + 1)
                return Result::badArgs;
            i++;
            _outFileName = argv[i];
            i++;
        }
        else if(std::strcmp(argv[i], "-f") == 0)
        {
            if(argc <= i + 1)
                return Result::badArgs;
            FilterDescriptor filterDescriptor;
            filterDescriptor.name = argv[i + 1];
            i += 2;

            while(i < argc && std::strcmp(argv[i], "-f") != 0 &&
                  std::strcmp(argv[i], "-o") != 0 &&
                  std::strcmp(argv[i], "-i") != 0)
            {
                filterDescriptor.params.push_back(argv[i]);
                i++;
            }

            _filterDescriptors.push_back(filterDescriptor);
        }
        else
        {
            return Result::badArgs;
        }
    }
    return Result::ok;
}
