#include "CmdLineArgs2PipelineConverter.h"

#include <stdexcept>

CmdLineArgs2PipelineConverter::CmdLineArgs2PipelineConverter() = default;

void CmdLineArgs2PipelineConverter::addFilterProducer(std::string filterName,
                                                      FilterProducer producer)
{
    _producers[filterName] = producer;
}
FilterProducer
CmdLineArgs2PipelineConverter::getFilterProducer(std::string filterName)
{
    auto it = _producers.find(filterName);
    if(it != _producers.end())
        return it->second;
    return nullptr;
}

Pipeline CmdLineArgs2PipelineConverter::createPipeline(
    const std::vector<FilterDescriptor>& filterDescriptors)
{
    Pipeline pipeline;
    for(const auto& fdesc: filterDescriptors)
    {
        FilterProducer producer = getFilterProducer(fdesc.name.c_str());
        if(producer)
        {
            IFilter* filter = producer(fdesc);
            if(filter)
                pipeline.addFilter(filter);
            else
                throw std::logic_error("Error creating filter " + fdesc.name);
        }
        else
        {
            throw std::logic_error("Unknown filter name " + fdesc.name);
        }
    }
    return pipeline;
}