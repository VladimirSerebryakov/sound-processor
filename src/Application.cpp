#include "Application.h"

#include "ArgsParser.h"
#include "FilterProducers.h"
#include "WAVReader.h"
#include "WAVWriter.h"

#include <iostream>

Application::Application() = default;
Application::~Application() = default;
void Application::configure()
{
    _cla2PipelineConverter.addFilterProducer(
        "ampl", FilterProducers::amplFilterCreator);
    _cla2PipelineConverter.addFilterProducer(
        "timestretch", FilterProducers::timestretchFilterCreator);
    _cla2PipelineConverter.addFilterProducer(
        "silence", FilterProducers::silenceFilterCreator);
    _cla2PipelineConverter.addFilterProducer(
        "lowpass", FilterProducers::lowpassFilterCreator);
    _cla2PipelineConverter.addFilterProducer(
        "normalize", FilterProducers::normalizeFilterCreator);
    _cla2PipelineConverter.addFilterProducer(
        "generator", FilterProducers::generatorFilterCreator);
}
size_t Application::start(int argc, char* argv[])
{
    try
    {
        configure();
    }
    catch(const std::exception& e)
    {
        std::cerr << "critical error of configuration: " << e.what()
                  << std::endl;
        return 1;
    }

    ArgsParser argsParser;
    ArgsParser::Result result = argsParser.parse(argc, argv);

    if(result == ArgsParser::Result::badArgs)
    {
        std::cerr << "Invalid command line arguments." << std::endl;
        printHelp(argv[0]);
        return 1;
    }

    if(result == ArgsParser::Result::noArgs)
    {
        printHelp(argv[0]);
        return 0;
    }

    try
    {
        const std::vector<FilterDescriptor>& filterDescriptors =
            argsParser.getFilterDescriptors();
        Pipeline pipeline =
            _cla2PipelineConverter.createPipeline(filterDescriptors);

        Waveform sound;
        if(argsParser.getInFileName() != nullptr)
            sound = WAVReader::read(argsParser.getInFileName());
        if(!pipeline.apply(&sound))
        {
            std::cerr << "Pipeline apply failed" << std::endl;
            return 1;
        }

        if(argsParser.getOutFileName() != nullptr)
            WAVWriter::write(argsParser.getOutFileName(), sound);
        return 0;
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}

void Application::printHelp(const char* appName)
{
    std::cout
        << " Sound Processor " << std::endl
        << "Сommand line format: " << std::endl
        << appName
        << " [-i <input.wav>] [-o <output.wav>] [-f <filter> [params...] ...]"
        << std::endl
        << std::endl
        << "Multiple filters can be used" << std::endl
        << "-i optional" << std::endl
        << std::endl
        << "Available filters: " << std::endl
        << "  -f ampl <factor>" << std::endl
        << "  -f silence <unit> <start> <end>" << std::endl
        << "  -f lowpass <WindowSize>" << std::endl
        << "  -f normalize <peak>" << std::endl
        << "  -f timestretch <factor>" << std::endl
        << "  -f generator <sin/am/fm> [params]" << std::endl
        << "[params] for sin: <durationMs> <frequency>" << std::endl
        << "[params] for am: <amplitude> <carrier> <modulation> <depth> "
           "<duration>"
        << std::endl
        << "[params] for fm: <amplitude> <carrier> <modulation> <deviation> "
           "<duration>"
        << std::endl;
}
