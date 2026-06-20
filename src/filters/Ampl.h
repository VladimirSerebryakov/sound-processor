//
// Created by vladi on 09.06.2026.
//

#ifndef SOUND_PROCESSOR_AMPL_H
#define SOUND_PROCESSOR_AMPL_H
#include "IFilter.h"

class Ampl: public IFilter
{
public:
    explicit Ampl(double factor);
    ~Ampl() override;

    bool apply(Waveform* sound) override;

protected:
    double _factor;
    static int16_t clamp(double value);
};

#endif  // SOUND_PROCESSOR_AMPL_H
