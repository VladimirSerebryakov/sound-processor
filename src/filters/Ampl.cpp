#include "Ampl.h"

#include <cmath>

Ampl::Ampl(double factor): _factor(factor) {}

Ampl::~Ampl() = default;

bool Ampl::apply(Waveform* sound)
{
    if(!sound)
        return false;

    std::vector<int16_t>& samples = sound->getSamples();

    for(size_t i = 0; i < samples.size(); ++i)
        samples[i] = clamp(samples[i] * _factor);

    return true;
}

int16_t Ampl::clamp(double value)
{
    if(value > 32767.0)
        return 32767;
    if(value < -32768.0)
        return -32768;
    return static_cast<int16_t>(std::round(value));
}
