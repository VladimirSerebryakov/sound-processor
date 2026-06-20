#include "Normalize.h"

#include <cmath>
#include <stdexcept>
Normalize::Normalize(double peak): _peak(peak) {}
Normalize::~Normalize() = default;
bool Normalize::apply(Waveform* sound)
{
    if(_peak < 0 || _peak > 1)
    {
        throw std::logic_error(
            "Peak must be between 0 and 1. The changes were not applied");
    }
    if(!sound)
        return false;
    int16_t curPeak = 0;
    std::vector<int16_t>& samples = sound->getSamples();
    for(size_t i = 0; i < sound->getSamplesCnt(); ++i)
        curPeak = std::max(curPeak, static_cast<int16_t>(std::abs(samples[i])));
    if(curPeak != 0)
    {
        const double SCALE = _peak * 32767.0 / curPeak;
        for(size_t i = 0; i < sound->getSamplesCnt(); ++i)
            samples[i] = static_cast<int16_t>(std::round(SCALE * samples[i]));
    }
    return true;
}