#ifndef SOUND_PROCESSOR_APPLICATION_H
#define SOUND_PROCESSOR_APPLICATION_H
#include "CmdLineArgs2PipelineConverter.h"

class Application
{
public:
    Application();
    ~Application();

    void configure();

    size_t start(int argc, char* argv[]);

protected:
    static void printHelp(const char* appName);

    CmdLineArgs2PipelineConverter _cla2PipelineConverter;
};

#endif  // SOUND_PROCESSOR_APPLICATION_H
