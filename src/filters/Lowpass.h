#ifndef SOUND_PROCESSOR_LOWPASS_H
#define SOUND_PROCESSOR_LOWPASS_H
#include "IFilter.h"

class Lowpass: public IFilter
{
public:
    explicit Lowpass(size_t windowSize);

    ~Lowpass() override;

    bool apply(Waveform* sound) override;

protected:
    size_t _windowSize;
};

#endif  // SOUND_PROCESSOR_LOWPASS_H
