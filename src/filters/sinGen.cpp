#include "sinGen.h"

#include <cmath>
#include <stdexcept>
SinGen::SinGen(double durationMs, double frequency)
    : AbstractGeneratorFilter(durationMs), _frequency(frequency)
{
}
SinGen::~SinGen() = default;

bool SinGen::apply(Waveform* sound)
{
    if(!sound)
        return false;
    if(_frequency < 0.0 || _durationMs < 0.0)
        throw std::logic_error("Invalid arg for SinGen filter");

    std::vector<int16_t>& samples = sound->getSamples();
    size_t samplesCnt = prepareSamples(sound);
    for(size_t i = 0; i < samplesCnt; i++)
    {
        double time = static_cast<double>(i) / sound->SAMPLE_RATE;
        samples[i] = clamp(32767 * std::sin(2 * M_PI * _frequency * time));
    }
    return true;
}