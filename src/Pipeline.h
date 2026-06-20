#ifndef SOUND_PROCESSOR_PIPELINE_H
#define SOUND_PROCESSOR_PIPELINE_H

#include "Waveform.h"
#include "filters/IFilter.h"
#include <vector>

class Pipeline
{
public:
    Pipeline();
    ~Pipeline();
    Pipeline(const Pipeline& other) = delete;
    Pipeline& operator=(const Pipeline& other) = delete;
    Pipeline(Pipeline&& other) noexcept;
    Pipeline& operator=(Pipeline&& other) noexcept;

    bool apply(Waveform* sound) const;
    IFilter* addFilter(IFilter* filter);
    size_t getFilterNumbers() const;
    IFilter* operator[](size_t index) const;

protected:
    std::vector<IFilter*> _filters;
};

#endif  // SOUND_PROCESSOR_PIPELINE_H