#ifndef SOUND_PROCESSOR_FILTERPRODUCERS_H
#define SOUND_PROCESSOR_FILTERPRODUCERS_H
#include "FilterDescriptor.h"
#include "filters/AmGen.h"
#include "filters/Ampl.h"
#include "filters/FmFilter.h"
#include "filters/Lowpass.h"
#include "filters/Normalize.h"
#include "filters/Silence.h"
#include "filters/Timestretch.h"
#include "filters/sinGen.h"

#include <complex>
#include <stdexcept>

namespace FilterProducers {

inline IFilter* amplFilterCreator(const FilterDescriptor& fdesc)
{
    if(fdesc.name != "ampl")
        throw std::logic_error("Wrong fdesc for ampl filter producer.");

    if(fdesc.params.size() < 1)
        throw std::logic_error("Wrong params number for ampl filter producer.");

    try
    {
        double ampl = std::stod(fdesc.params[0]);

        IFilter* amplFilter = new Ampl(ampl);
        return amplFilter;
    }
    catch(const std::invalid_argument& e)
    {
        throw std::logic_error("Error converting arguments of ampl filter.");
    }
}

inline IFilter* silenceFilterCreator(const FilterDescriptor& fdesc)
{
    if(fdesc.name != "silence")
        throw std::logic_error("Wrong fdesc for silence filter producer.");

    if(fdesc.params.size() < 3)
    {
        throw std::logic_error(
            "Wrong params number for silence filter producer.");
    }

    try
    {
        std::string unit = fdesc.params[0];
        double start = std::stod(fdesc.params[1]);
        double end = std::stod(fdesc.params[2]);

        IFilter* silenceFilter = new Silence(unit, start, end);
        return silenceFilter;
    }
    catch(const std::invalid_argument& e)
    {
        throw std::logic_error("Error converting arguments of silence filter.");
    }
}

inline IFilter* lowpassFilterCreator(const FilterDescriptor& fdesc)
{
    if(fdesc.name != "lowpass")
        throw std::logic_error("Wrong fdesc for lowpass filter producer.");

    if(fdesc.params.size() < 1)
    {
        throw std::logic_error(
            "Wrong params number for lowpass filter producer.");
    }

    try
    {
        size_t windowSize = std::stoi(fdesc.params[0]);

        IFilter* lowpass = new Lowpass(windowSize);
        return lowpass;
    }
    catch(const std::invalid_argument& e)
    {
        throw std::logic_error("Error converting arguments of lowpass filter.");
    }
}

inline IFilter* normalizeFilterCreator(const FilterDescriptor& fdesc)
{
    if(fdesc.name != "normalize")
        throw std::logic_error("Wrong fdesc for normalize filter producer.");

    if(fdesc.params.size() < 1)
    {
        throw std::logic_error(
            "Wrong params number for normalize filter producer.");
    }

    try
    {
        double peak = std::stod(fdesc.params[0]);

        IFilter* normalizeFilter = new Normalize(peak);
        return normalizeFilter;
    }
    catch(const std::invalid_argument& e)
    {
        throw std::logic_error(
            "Error converting arguments of normalize filter.");
    }
}

inline IFilter* timestretchFilterCreator(const FilterDescriptor& fdesc)
{
    if(fdesc.name != "timestretch")
        throw std::logic_error("Wrong fdesc for timestretch filter producer.");

    if(fdesc.params.size() < 1)
    {
        throw std::logic_error(
            "Wrong params number for timestretch filter producer.");
    }

    try
    {
        double factor = std::stod(fdesc.params[0]);

        IFilter* timestretchFilter = new Timestretch(factor);
        return timestretchFilter;
    }
    catch(const std::invalid_argument& e)
    {
        throw std::logic_error(
            "Error converting arguments of timestretch filter.");
    }
}

inline IFilter* generatorFilterCreator(const FilterDescriptor& fdesc)
{
    if(fdesc.name != "generator")
        throw std::logic_error("Wrong fdesc for generator filter producer.");
    if(fdesc.params.size() < 1)
    {
        throw std::logic_error(
            "Wrong params number for generator filter producer.");
    }
    try
    {
        if(fdesc.params[0] == "sin")
        {
            if(fdesc.params.size() < 3)
            {
                throw std::logic_error(
                    "Wrong params number for sin generator filter producer.");
            }
            double durationMs = std::stod(fdesc.params[1]);
            double frequency = std::stod(fdesc.params[2]);

            IFilter* sinFilter = new SinGen(durationMs, frequency);
            return sinFilter;
        }
        else if(fdesc.params[0] == "am")
        {
            if(fdesc.params.size() < 6)
            {
                throw std::logic_error(
                    "Wrong params number for am generator filter producer.");
            }
            double amplitude = std::stod(fdesc.params[1]);
            double carrier = std::stod(fdesc.params[2]);
            double modulation = std::stod(fdesc.params[3]);
            double depth = std::stod(fdesc.params[4]);
            double duration = std::stod(fdesc.params[5]);

            IFilter* amFilter =
                new AmGen(amplitude, carrier, modulation, depth, duration);
            return amFilter;
        }
        else if(fdesc.params[0] == "fm")
        {
            if(fdesc.params.size() < 6)
            {
                throw std::logic_error(
                    "Wrong params number for fm generator filter producer.");
            }
            double amplitude = std::stod(fdesc.params[1]);
            double carrier = std::stod(fdesc.params[2]);
            double modulation = std::stod(fdesc.params[3]);
            double deviation = std::stod(fdesc.params[4]);
            double duration = std::stod(fdesc.params[5]);
            IFilter* fmFilter = new FmFilter(amplitude, carrier, modulation,
                                             deviation, duration);
            return fmFilter;
        }
        throw std::logic_error("Wrong generator filter type.");
    }
    catch(const std::invalid_argument& e)
    {
        throw std::logic_error(
            "Error converting arguments of generator filter producer.");
    }
}

}  // namespace FilterProducers

#endif  // SOUND_PROCESSOR_FILTERPRODUCERS_H
