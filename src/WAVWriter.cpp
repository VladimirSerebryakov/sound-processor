#include "WAVWriter.h"
#include "WAVHeader.h"

#include <cstring>
#include <fstream>

void WAVWriter::write(const std::string& path, const Waveform& wave)
{
    std::ofstream file(path, std::ios::binary);
    if(!file)
        throw std::runtime_error("File opening error" + path);

    RiffHeader riffHeader;
    std::memcpy(riffHeader.groupID, "RIFF", 4);
    riffHeader.size = 36 + wave.getSamplesCnt() * 2;
    std::memcpy(riffHeader.riffType, "WAVE", 4);

    FmtHeader fmtHeader;
    std::memcpy(fmtHeader.chunkID, "fmt ", 4);
    fmtHeader.chunkSize = 16;
    fmtHeader.wFormatTag = 1;
    fmtHeader.wChannels = 1;
    fmtHeader.dwSamplesPerSec = Waveform::SAMPLE_RATE;
    fmtHeader.wBitsPerSample = 16;
    fmtHeader.dwAvgBytesPerSec = Waveform::SAMPLE_RATE * 2;
    fmtHeader.wBlockAlign = 2;

    WaveformHeader waveHeader;
    std::memcpy(waveHeader.chunkID, "data", 4);
    waveHeader.chunkSize = wave.getSamplesCnt() * 2;

    file.write(reinterpret_cast<char*>(&riffHeader), sizeof(riffHeader));
    file.write(reinterpret_cast<char*>(&fmtHeader), sizeof(fmtHeader));
    file.write(reinterpret_cast<char*>(&waveHeader), sizeof(waveHeader));

    file.write(reinterpret_cast<const char*>(wave.getSamples().data()),
               wave.getSamplesCnt() * 2);
}