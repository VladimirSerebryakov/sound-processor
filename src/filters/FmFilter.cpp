#include "FmFilter.h"

#include <cmath>
#include <stdexcept>

FmFilter::FmFilter(double amplitude, double carrier, double modulation,
                   double deviation, double duration)
    : AbstractGeneratorFilter(duration), _amplitude(amplitude),
      _carrier(carrier), _modulation(modulation), _deviation(deviation)
{
}
FmFilter::~FmFilter() = default;
bool FmFilter::apply(Waveform* sound)
{
    if(!sound)
        return false;
    if(_durationMs < 0.0 || _amplitude < 0.0 || _amplitude > 1.0 ||
       _carrier < 0.0 || _modulation < 0.0 || _deviation < 0.0)
    {
        throw std::logic_error("Invalid arguments for FMGen filter");
    }

    size_t samplesCnt = prepareSamples(sound);
    std::vector<int16_t>& samples = sound->getSamples();

    for(size_t i = 0; i < samplesCnt; i++)
    {
        double time = static_cast<double>(i) / Waveform::SAMPLE_RATE;
        double devMod;
        if(_modulation == 0.0)
            devMod = 0.0;
        else
            devMod = _deviation / _modulation;
        const double PHASE = 2 * M_PI * _carrier * time +
                             (devMod)*std::sin(2 * _modulation * M_PI * time);
        samples[i] = clamp(_amplitude * 32767 * std::sin(PHASE));
    }

    return true;
}