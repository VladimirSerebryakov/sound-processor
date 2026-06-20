#ifndef SOUND_PROCESSOR_FMFILTER_H
#define SOUND_PROCESSOR_FMFILTER_H
#include "AbstractGeneratorFilter.h"

class FmFilter: public AbstractGeneratorFilter
{
public:
    FmFilter(double amplitude, double carrier, double modulation,
             double deviation, double duration);
    ~FmFilter() override;

    bool apply(Waveform* sound) override;

protected:
    double _amplitude;
    double _carrier;
    double _modulation;
    double _deviation;
};

#endif  // SOUND_PROCESSOR_FMFILTER_H
