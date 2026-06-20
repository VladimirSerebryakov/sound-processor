#ifndef SOUND_PROCESSOR_WAVWRITER_H
#define SOUND_PROCESSOR_WAVWRITER_H
#include "Waveform.h"

#include <string>

class WAVWriter
{
public:
    WAVWriter() = default;
    ~WAVWriter() = default;

    static void write(const std::string& path, const Waveform& wav);
};

#endif  // SOUND_PROCESSOR_WAVWRITER_H
