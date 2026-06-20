#ifndef SOUND_PROCESSOR_SINGEN_H
#define SOUND_PROCESSOR_SINGEN_H
#include "AbstractGeneratorFilter.h"

class SinGen: public AbstractGeneratorFilter
{
public:
    SinGen(double durationMs, double frequency);
    ~SinGen() override;

    bool apply(Waveform* sound) override;

protected:
    double _frequency;
};

#endif  // SOUND_PROCESSOR_SINGEN_H
