#include "Timestretch.h"

#include <cmath>
#include <stdexcept>
Timestretch::Timestretch(double factor): _factor(factor) {}
Timestretch::~Timestretch() = default;
bool Timestretch::apply(Waveform* sound)
{
    if(_factor <= 0.0)
        throw std::logic_error("Invalid argument for Timestretch filter");
    if(!sound)
        return false;
    const std::vector<int16_t>& oldSamples = sound->getSamples();
    size_t oldSize = sound->getSamplesCnt();
    if(oldSize == 0)
        return true;
    auto newSize = static_cast<size_t>(std::round(oldSize * _factor));
    std::vector<int16_t> newSamples(newSize);
    for(size_t i = 0; i < newSize; i++)
    {
        double pos = static_cast<double>(i) / _factor;
        auto leftIdx = static_cast<size_t>(std::floor(pos));
        double frac = pos - static_cast<double>(leftIdx);
        if(leftIdx + 1 < oldSize)
        {
            double newSamp =
                static_cast<double>(oldSamples[leftIdx]) * (1.0 - frac) +
                static_cast<double>(oldSamples[leftIdx + 1]) * (frac);
            newSamples[i] = static_cast<int16_t>(std::round(newSamp));
        }
        else
        {
            newSamples[i] = oldSamples[leftIdx];
        }
    }
    sound->getSamples() = std::move(newSamples);
    return true;
}