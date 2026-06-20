#ifndef SOUND_PROCESSOR_WAVHEADER_H
#define SOUND_PROCESSOR_WAVHEADER_H
#include <cstdint>

struct __attribute__((packed)) RiffHeader
{
    char groupID[4];
    uint32_t size;
    char riffType[4];
};

struct __attribute__((packed)) FmtHeader
{
    char chunkID[4];
    uint32_t chunkSize;
    uint16_t wFormatTag;
    uint16_t wChannels;
    uint32_t dwSamplesPerSec;
    uint32_t dwAvgBytesPerSec;
    uint16_t wBlockAlign;
    uint16_t wBitsPerSample;
};

struct __attribute__((packed)) WaveformHeader
{
    char chunkID[4];
    uint32_t chunkSize;
};

#endif  // SOUND_PROCESSOR_WAVHEADER_H
