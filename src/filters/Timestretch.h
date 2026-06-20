#ifndef SOUND_PROCESSOR_TIMESTRETCH_H
#define SOUND_PROCESSOR_TIMESTRETCH_H
#include "IFilter.h"

class Timestretch: public IFilter
{
public:
    explicit Timestretch(double factor);
    ~Timestretch() override;

    bool apply(Waveform* sound) override;

private:
    double _factor;
};

#endif  // SOUND_PROCESSOR_TIMESTRETCH_H
