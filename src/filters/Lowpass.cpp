#include "Lowpass.h"

#include <cmath>
#include <stdexcept>
Lowpass::Lowpass(size_t windowSize): _windowSize(windowSize) {}
Lowpass::~Lowpass() = default;

bool Lowpass::apply(Waveform* sound)
{
    if(_windowSize < 1 || _windowSize % 2 != 1)
        throw std::logic_error("Incorrect parameter for the filter Lowpass");
    if(!sound)
        return false;
    const std::vector<int16_t>& oldSamples = sound->getSamples();
    size_t size = oldSamples.size();

    std::vector<int16_t> newSamples(size);
    int radius = (_windowSize - 1) / 2;
    double curSum = 0.0;

    for(int i = -radius; i <= radius; i++)
        if(i < 0)
            curSum += static_cast<double>(oldSamples[0]);
        else if(i >= static_cast<int>(size))
            curSum += static_cast<double>(oldSamples[size - 1]);
        else
            curSum += static_cast<double>(oldSamples[i]);
    newSamples[0] = static_cast<int16_t>(std::round(curSum / _windowSize));

    for(size_t i = 1; i < size; i++)
    {
        int leftIndex = i - 1 - radius;
        int rightIndex = i + radius;
        if(leftIndex < 0)
            curSum -= static_cast<double>(oldSamples[0]);
        else
            curSum -= static_cast<double>(oldSamples[leftIndex]);

        if(rightIndex >= static_cast<int>(size))
            curSum += static_cast<double>(oldSamples[size - 1]);
        else
            curSum += static_cast<double>(oldSamples[rightIndex]);

        newSamples[i] = static_cast<int16_t>(std::round(curSum / _windowSize));
    }

    sound->getSamples() = std::move(newSamples);

    return true;
}