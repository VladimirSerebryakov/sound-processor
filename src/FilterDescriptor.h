#ifndef SOUND_PROCESSOR_FILTERDESCRIPTOR_H
#define SOUND_PROCESSOR_FILTERDESCRIPTOR_H

#include <string>
#include <vector>

struct FilterDescriptor
{
    std::string name;
    std::vector<std::string> params;
};

#endif  // SOUND_PROCESSOR_FILTERDESCRIPTOR_H
