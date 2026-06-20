#ifndef SOUND_PROCESSOR_IFILTER_H
#define SOUND_PROCESSOR_IFILTER_H
#include "../Waveform.h"

class IFilter
{
public:
    virtual ~IFilter() = default;

    virtual bool apply(Waveform* sound) = 0;
};

#endif  // SOUND_PROCESSOR_IFILTER_H
