#ifndef SOUND_PROCESSOR_AMGEN_H
#define SOUND_PROCESSOR_AMGEN_H
#include "AbstractGeneratorFilter.h"

class AmGen: public AbstractGeneratorFilter
{
public:
    AmGen(double amplitude, double carrier, double modulation, double depth,
          double duration);
    ~AmGen() override;

    bool apply(Waveform* sound) override;

protected:
    double _amplitude;
    double _carrier;
    double _modulation;
    double _depth;
};

#endif  // SOUND_PROCESSOR_AMGEN_H
