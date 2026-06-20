#ifndef SOUND_PROCESSOR_WAVEFORM_H
#define SOUND_PROCESSOR_WAVEFORM_H
#include <cstdint>
#include <vector>

class Waveform
{
public:
    static constexpr size_t SAMPLE_RATE = 44100;

    Waveform() = default;
    Waveform(size_t samplesCnt);

    ~Waveform() = default;

    static size_t secondToSamples(double seconds);

    static double samplesToSeconds(size_t samplesCnt);

    static double samplesToMs(size_t samplesCnt);

    static size_t msToSamples(double msec);

    void setSamplesCnt(size_t samplesCnt);

    size_t getSamplesCnt() const;

    double getSecondsDuration() const;

    std::vector<int16_t>& getSamples();
    const std::vector<int16_t>& getSamples() const;

protected:
    std::vector<int16_t> _samples;
};

#endif  // SOUND_PROCESSOR_WAVEFORM_H