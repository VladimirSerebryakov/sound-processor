#include "WAVReader.h"
#include "WAVHeader.h"
#include "Waveform.h"

#include <fstream>
#include <ios>

Waveform WAVReader::read(const std::string& path)
{
    std::ifstream file(path, std::ios::binary);
    if(!file)
        throw std::runtime_error("File opening error " + path);

    RiffHeader riffHdr;
    file.read(reinterpret_cast<char*>(&riffHdr), sizeof(riffHdr));
    if(!file || std::string(riffHdr.groupID, 4) != "RIFF" ||
       std::string(riffHdr.riffType, 4) != "WAVE")
    {
        throw std::runtime_error("Invalid RIFF/WAVE file " + path);
    }
    FmtHeader fmtHdr;
    file.read(reinterpret_cast<char*>(&fmtHdr), sizeof(fmtHdr));
    if(!file || std::string(fmtHdr.chunkID, 4) != "fmt " ||
       fmtHdr.chunkSize != 16 || fmtHdr.wFormatTag != 1 ||
       fmtHdr.wChannels != 1 || fmtHdr.dwSamplesPerSec != 44100 ||
       fmtHdr.dwAvgBytesPerSec != 88200 || fmtHdr.wBlockAlign != 2 ||
       fmtHdr.wBitsPerSample != 16)
    {
        throw std::runtime_error("File format is not supported " + path);
    }
    WaveformHeader waveHdr;
    file.read(reinterpret_cast<char*>(&waveHdr), sizeof(waveHdr));
    if(std::string(waveHdr.chunkID, 4) != "data")
        throw std::runtime_error("Expected data chunk in file " + path);

    Waveform wav;
    wav.setSamplesCnt(waveHdr.chunkSize / fmtHdr.wBlockAlign);
    file.read(reinterpret_cast<char*>(wav.getSamples().data()),
              waveHdr.chunkSize);
    if(!file)
        throw std::runtime_error("File reading error " + path);

    return wav;
}
