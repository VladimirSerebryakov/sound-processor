#ifndef SOUND_PROCESSOR_ARGSPARSER_H
#define SOUND_PROCESSOR_ARGSPARSER_H
#include "FilterDescriptor.h"

#include <vector>

class ArgsParser
{
public:
    enum class Result
    {
        ok,
        noArgs,
        badArgs
    };

    ArgsParser();
    ~ArgsParser();

    Result parse(int argc, char* argv[]);

    const char* getInFileName() const { return _inFileName; }
    const char* getOutFileName() const { return _outFileName; }

    const std::vector<FilterDescriptor>& getFilterDescriptors() const
    {
        return _filterDescriptors;
    }

private:
    char* _inFileName;
    char* _outFileName;
    std::vector<FilterDescriptor> _filterDescriptors;
};

#endif  // SOUND_PROCESSOR_ARGSPARSER_H
