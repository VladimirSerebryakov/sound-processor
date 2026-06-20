#ifndef SOUND_PROCESSOR_NORMALIZE_H
#define SOUND_PROCESSOR_NORMALIZE_H
#include "IFilter.h"

class Normalize: public IFilter
{
public:
    explicit Normalize(double peak);
    ~Normalize() override;

    bool apply(Waveform* sound) override;

protected:
    double _peak;
};

#endif  // SOUND_PROCESSOR_NORMALIZE_H
