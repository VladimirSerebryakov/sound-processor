#include "Pipeline.h"

#include <iostream>
#include <ostream>
#include <stdexcept>

Pipeline::Pipeline() = default;
Pipeline::~Pipeline()
{
    for(IFilter* filter: _filters)
        delete filter;
}
Pipeline::Pipeline(Pipeline&& other) noexcept = default;
Pipeline& Pipeline::operator=(Pipeline&& other) noexcept = default;
bool Pipeline::apply(Waveform* sound) const
{
    if(!sound)
        return false;
    size_t i = 1;
    for(IFilter* filter: _filters)
    {
        try
        {
            filter->apply(sound);
        }
        catch(const std::logic_error& error)
        {
            std::cerr << "Pipeline failed. Step " << i
                      << "failed with logic error (invalid parameters): "
                      << error.what() << std::endl;
            return false;
        }
        catch(const std::exception& error)
        {
            std::cerr << "Pipeline failed. Step " << i
                      << "failed with an unspecified error: " << error.what()
                      << std::endl;
            return false;
        }
        i++;
    }
    return true;
}
IFilter* Pipeline::addFilter(IFilter* filter)
{
    if(filter != nullptr)
        _filters.push_back(filter);
    return filter;
}
size_t Pipeline::getFilterNumbers() const { return _filters.size(); }
IFilter* Pipeline::operator[](size_t index) const
{
    if(index >= getFilterNumbers())
        throw std::out_of_range("Index out of range");
    return _filters[index];
}