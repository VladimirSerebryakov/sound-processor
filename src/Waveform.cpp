#include "Waveform.h"

Waveform::Waveform(size_t samplesCnt) { _samples.resize(samplesCnt, 0); }

size_t Waveform::secondToSamples(double seconds)
{
    return static_cast<size_t>(seconds * SAMPLE_RATE);
}

double Waveform::samplesToSeconds(size_t samplesCnt)
{
    return static_cast<double>(samplesCnt) / SAMPLE_RATE;
}
double Waveform::samplesToMs(size_t samplesCnt)
{
    return static_cast<double>(samplesCnt) * 1000.0 / SAMPLE_RATE;
}

size_t Waveform::msToSamples(double msec)
{
    return static_cast<size_t>(msec / 1000.0 * SAMPLE_RATE);
}

void Waveform::setSamplesCnt(size_t samplesCnt)
{
    _samples.resize(samplesCnt, 0);
}

size_t Waveform::getSamplesCnt() const { return _samples.size(); }

double Waveform::getSecondsDuration() const
{
    return static_cast<double>(getSamplesCnt()) / SAMPLE_RATE;
}

std::vector<int16_t>& Waveform::getSamples() { return _samples; }
const std::vector<int16_t>& Waveform::getSamples() const { return _samples; }
