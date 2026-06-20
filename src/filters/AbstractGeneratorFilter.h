#ifndef SOUND_PROCESSOR_ABSTRACTGENERATORFILTER_H
#define SOUND_PROCESSOR_ABSTRACTGENERATORFILTER_H
#include "IFilter.h"

class AbstractGeneratorFilter: public IFilter
{
public:
    explicit AbstractGeneratorFilter(double durationMs);
    ~AbstractGeneratorFilter() override;

protected:
    double _durationMs;
    size_t prepareSamples(Waveform* sound) const;
    static int16_t clamp(double val);
};

#endif  // SOUND_PROCESSOR_ABSTRACTGENERATORFILTER_H
