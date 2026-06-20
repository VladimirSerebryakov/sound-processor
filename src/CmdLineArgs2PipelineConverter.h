#ifndef SOUND_PROCESSOR_CMDLINEARGS2PIPELINECONVERTER_H
#define SOUND_PROCESSOR_CMDLINEARGS2PIPELINECONVERTER_H
#include "FilterDescriptor.h"
#include "Pipeline.h"

#include <map>

using FilterProducer = IFilter* (*)(const FilterDescriptor&);

class CmdLineArgs2PipelineConverter
{
public:
    CmdLineArgs2PipelineConverter();

    Pipeline
    createPipeline(const std::vector<FilterDescriptor>& filterDescriptors);

    void addFilterProducer(std::string filterName, FilterProducer producer);
    FilterProducer getFilterProducer(std::string filterName);

private:
    std::map<std::string, FilterProducer> _producers;
};

#endif  // SOUND_PROCESSOR_CMDLINEARGS2PIPELINECONVERTER_H
