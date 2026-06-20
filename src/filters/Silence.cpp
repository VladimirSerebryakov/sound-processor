#include "Silence.h"

#include <stdexcept>

Silence::Silence(const std::string& unit, double start, double end)
    : _unit(unit), _start(start), _end(end)
{
}
Silence::~Silence() = default;
bool Silence::apply(Waveform* sound)
{
    if(!sound)
        return false;
    if(_start < 0 || _end < _start ||
       !(_unit == "sec" || _unit == "ms" || _unit == "samples"))
        throw std::logic_error("Not valid arguments for Silence filter");
    size_t startSample;
    size_t endSample;

    if(_unit == "sec")
    {
        startSample = Waveform::secondToSamples(_start);
        endSample = Waveform::secondToSamples(_end);
    }
    else if(_unit == "ms")
    {
        startSample = Waveform::msToSamples(_start);
        endSample = Waveform::msToSamples(_end);
    }
    else
    {
        startSample = static_cast<size_t>(_start);
        endSample = static_cast<size_t>(_end);
    }
    size_t samplesCnt = sound->getSamplesCnt();
    std::vector<int16_t>& samples = sound->getSamples();

    if(endSample > samplesCnt)
        sound->setSamplesCnt(endSample);
    for(size_t i = startSample; i <= endSample && i < samples.size(); ++i)
        samples[i] = 0;
    return true;
}