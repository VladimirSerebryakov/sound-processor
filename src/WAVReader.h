#ifndef SOUND_PROCESSOR_WAVREADER_H
#define SOUND_PROCESSOR_WAVREADER_H

#include "Waveform.h"

#include <string>

class WAVReader
{
public:
    WAVReader() = default;
    ~WAVReader() = default;

    static Waveform read(const std::string& path);
};

#endif  // SOUND_PROCESSOR_WAVREADER_H
