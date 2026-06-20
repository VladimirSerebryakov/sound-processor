cmake_minimum_required(VERSION 4.1)
project(sound_processor)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.4.0
)

FetchContent_MakeAvailable(Catch2)

add_executable(sound_processor src/main.cpp
        src/Waveform.h
        src/Waveform.cpp
        src/WAVHeader.h
        src/WAVReader.h
        src/WAVWriter.cpp
        src/WAVWriter.h
        src/WAVReader.cpp
        src/filters/IFilter.h
        src/filters/Ampl.cpp
        src/filters/Ampl.h
        src/filters/Normalize.cpp
        src/filters/Normalize.h
        src/filters/Silence.cpp
        src/filters/Silence.h
        src/filters/Timestretch.cpp
        src/filters/Timestretch.h
        src/filters/Lowpass.cpp
        src/filters/Lowpass.h
        src/filters/AbstractGeneratorFilter.cpp
        src/filters/AbstractGeneratorFilter.h
        src/filters/sinGen.cpp
        src/filters/sinGen.h
        src/filters/AmGen.cpp
        src/filters/AmGen.h
        src/filters/FmFilter.cpp
        src/filters/FmFilter.h
        src/Pipeline.cpp
        src/Pipeline.h
        src/CmdLineArgs2PipelineConverter.cpp
        src/CmdLineArgs2PipelineConverter.h
        src/FilterDescriptor.h
        src/FilterProducers.h
        src/Application.cpp
        src/Application.h
        src/ArgsParser.cpp
        src/ArgsParser.h
)

add_executable(test_sound_processor test.cpp
        src/Waveform.h
        src/Waveform.cpp
        src/WAVHeader.h
        src/WAVReader.h
        src/WAVWriter.cpp
        src/WAVWriter.h
        src/WAVReader.cpp
        src/filters/IFilter.h
        src/filters/Ampl.cpp
        src/filters/Ampl.h
        src/filters/Normalize.cpp
        src/filters/Normalize.h
        src/filters/Silence.cpp
        src/filters/Silence.h
        src/filters/Timestretch.cpp
        src/filters/Timestretch.h
        src/filters/Lowpass.cpp
        src/filters/Lowpass.h
        src/filters/AbstractGeneratorFilter.cpp
        src/filters/AbstractGeneratorFilter.h
        src/filters/sinGen.cpp
        src/filters/sinGen.h
        src/filters/AmGen.cpp
        src/filters/AmGen.h
        src/filters/FmFilter.cpp
        src/filters/FmFilter.h
        src/Pipeline.cpp
        src/Pipeline.h
        src/CmdLineArgs2PipelineConverter.cpp
        src/CmdLineArgs2PipelineConverter.h
        src/FilterDescriptor.h
        src/FilterProducers.h
        src/Application.cpp
        src/Application.h
        src/ArgsParser.cpp
        src/ArgsParser.h
        test.cpp
)
target_link_libraries(test_sound_processor PRIVATE Catch2::Catch2WithMain)

target_include_directories(test_sound_processor PRIVATE src src/filters)

