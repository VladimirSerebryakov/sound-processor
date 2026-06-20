#include "AmGen.h"

#include <cmath>
#include <stdexcept>

AmGen::AmGen(double amplitude, double carrier, double modulation, double depth,
             double duration)
    : AbstractGeneratorFilter(duration), _amplitude(amplitude),
      _carrier(carrier), _modulation(modulation), _depth(depth)
{
}
AmGen::~AmGen() = default;

bool AmGen::apply(Waveform* sound)
{
    if(!sound)
        return false;
    if(_amplitude < 0.0 || _amplitude > 1.0 || _carrier < 0.0 ||
       _modulation < 0.0 || _depth < 0.0 || _depth > 1.0 || _durationMs < 0.0)
    {
        throw std::logic_error("Invalid arg for SinGen filter");
    }

    std::vector<int16_t>& samples = sound->getSamples();
    size_t samplesCnt = prepareSamples(sound);

    for(size_t i = 0; i < samplesCnt; i++)
    {
        const double TEMP = static_cast<double>(i) / sound->SAMPLE_RATE;
        const double ENVELOPE =
            1.0 + _depth * std::sin(2 * M_PI * _modulation * TEMP);
        const double CARRIER = std::sin(2.0 * M_PI * _carrier * TEMP);
        samples[i] = clamp(_amplitude * 32767 * ENVELOPE * CARRIER);
    }
    return true;
}