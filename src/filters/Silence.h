#ifndef SOUND_PROCESSOR_SILENCE_H
#define SOUND_PROCESSOR_SILENCE_H
#include "IFilter.h"

#include <string>

class Silence: public IFilter
{
public:
    explicit Silence(const std::string& unit, double start, double end);
    ~Silence() override;

    bool apply(Waveform* sound) override;

protected:
    std::string _unit;
    double _start;
    double _end;
};

#endif  // SOUND_PROCESSOR_SILENCE_H
