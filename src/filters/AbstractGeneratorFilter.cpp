#include "AbstractGeneratorFilter.h"

#include <cmath>

AbstractGeneratorFilter::AbstractGeneratorFilter(double durationMs)
    : _durationMs(durationMs)
{
}
AbstractGeneratorFilter::~AbstractGeneratorFilter() = default;
size_t AbstractGeneratorFilter::prepareSamples(Waveform* sound) const
{
    if(!sound)
        return 0;
    size_t samplesCnt = Waveform::msToSamples(_durationMs);
    sound->setSamplesCnt(samplesCnt);
    return samplesCnt;
}
int16_t AbstractGeneratorFilter::clamp(double val)
{
    if(val > 32767.0)
        return 32767;
    if(val < -32768.0)
        return -32768;
    return static_cast<int16_t>(std::round(val));
}
