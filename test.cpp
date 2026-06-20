#include "ArgsParser.h"
#include "CmdLineArgs2PipelineConverter.h"
#include "FilterProducers.h"
#include "Waveform.h"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Waveform time and samples")
{
    REQUIRE(Waveform::SAMPLE_RATE == 44100);

    SECTION("Seconds and samples")
    {
        CHECK(Waveform::secondToSamples(1.0) == 44100);
        CHECK(Waveform::secondToSamples(0.5) == 22050);

        CHECK(Waveform::samplesToSeconds(44100) == 1.0);
        CHECK(Waveform::samplesToSeconds(22050) == 0.5);
    }

    SECTION("Milliseconds and samples")
    {
        CHECK(Waveform::msToSamples(1000.0) == 44100);
        CHECK(Waveform::msToSamples(500.0) == 22050);

        CHECK(Waveform::samplesToMs(22050) == 500.0);
        CHECK(Waveform::samplesToMs(44100) == 1000.0);
    }
}

TEST_CASE("ArgsParser tests")
{
    ArgsParser parser;

    SECTION("Valid command line arguments")
    {
        char* argv[] = {const_cast<char*>("sound_processor"),
                        const_cast<char*>("-i"),
                        const_cast<char*>("input.wav"),
                        const_cast<char*>("-o"),
                        const_cast<char*>("output.wav"),
                        const_cast<char*>("-f"),
                        const_cast<char*>("ampl"),
                        const_cast<char*>("0.5")};
        int argc = 8;
        ArgsParser::Result res = parser.parse(argc, argv);
        REQUIRE(res == ArgsParser::Result::ok);
        CHECK(std::strcmp(parser.getInFileName(), "input.wav") == 0);
        CHECK(std::strcmp(parser.getOutFileName(), "output.wav") == 0);
        const std::vector<FilterDescriptor>& filterDescriptors =
            parser.getFilterDescriptors();
        REQUIRE(filterDescriptors.size() == 1);
        CHECK(filterDescriptors[0].name == "ampl");
        REQUIRE(filterDescriptors[0].params.size() == 1);
        CHECK(filterDescriptors[0].params[0] == "0.5");
    }

    SECTION("No arguments in command line")
    {
        char* argv1[] = {const_cast<char*>("sound_processor")};
        int argc = 1;
        CHECK(parser.parse(argc, argv1) == ArgsParser::Result::noArgs);

        char* argv2[] = {const_cast<char*>("sound_processor"),
                         const_cast<char*>("-h")};
        argc = 2;
        CHECK(parser.parse(argc, argv2) == ArgsParser::Result::noArgs);
    }

    SECTION("Bad arguments in command line")
    {
        char* argvNoInFile[] = {
            const_cast<char*>("sound_processor"), const_cast<char*>("-i"),
            const_cast<char*>("-f"), const_cast<char*>("ampl"),
            const_cast<char*>("0.5")};
        CHECK(parser.parse(5, argvNoInFile) == ArgsParser::Result::badArgs);

        char* argvNoOutFile[] = {
            const_cast<char*>("sound_processor"), const_cast<char*>("-o"),
            const_cast<char*>("-f"), const_cast<char*>("ampl"),
            const_cast<char*>("0.5")};
        CHECK(parser.parse(5, argvNoOutFile) == ArgsParser::Result::badArgs);

        char* argvBadFlag[] = {const_cast<char*>("sound_processor"),
                               const_cast<char*>("-k")};
        CHECK(parser.parse(2, argvBadFlag) == ArgsParser::Result::badArgs);
    }
}

TEST_CASE("Pipeline Converter tests", "[converter]")
{
    CmdLineArgs2PipelineConverter converter;
    converter.addFilterProducer("ampl", FilterProducers::amplFilterCreator);

    SECTION("Create pipeline with correct descriptor")
    {
        std::vector<FilterDescriptor> descriptors = {
            FilterDescriptor{.name = "ampl", .params = {"1.0"}}};
        Pipeline pipeline = converter.createPipeline(descriptors);
        CHECK(pipeline.getFilterNumbers() == 1);
    }

    SECTION("Unknown filter name in despriptor")
    {
        std::vector<FilterDescriptor> descriptors = {
            FilterDescriptor{.name = "unknown", .params = {"1"}}};
        CHECK_THROWS_AS(converter.createPipeline(descriptors),
                        std::logic_error);
    }
}

TEST_CASE("Filters tests")
{
    SECTION("Ampl filter check")
    {
        Waveform sound(3);
        std::vector<int16_t>& samples = sound.getSamples();
        samples[0] = 1000;
        samples[1] = -500;
        samples[2] = 0;
        Ampl amplFilter(2.0);
        CHECK(amplFilter.apply(&sound) == true);
        CHECK(samples[0] == 2000);
        CHECK(samples[1] == -1000);
        CHECK(samples[2] == 0);
    }

    SECTION("Silence filter check")
    {
        Waveform sound(4);
        std::vector<int16_t>& samples = sound.getSamples();
        samples[0] = 1000;
        samples[1] = -500;
        samples[2] = 3;
        samples[3] = 100;
        Silence silenceFilter("samples", 1.0, 2.0);
        CHECK(silenceFilter.apply(&sound) == true);
        CHECK(samples[0] == 1000);
        CHECK(samples[1] == 0);
        CHECK(samples[2] == 0);
        CHECK(samples[3] == 100);
    }

    SECTION("Normalize filter check")
    {
        Waveform sound(3);
        std::vector<int16_t>& samples = sound.getSamples();
        samples[0] = 1;
        samples[1] = 16384;
        samples[2] = 2;
        Normalize normalizeFilter(1.0);
        CHECK(normalizeFilter.apply(&sound) == true);
        CHECK(samples[0] == 2);
        CHECK(samples[1] == 32767);
        CHECK(samples[2] == 4);
    }

    SECTION("Timestretch filter check")
    {
        Waveform sound(3);
        std::vector<int16_t>& samples = sound.getSamples();
        samples[0] = 1;
        samples[1] = 2;
        samples[2] = 3;
        Timestretch stretchFilter(2.0);
        CHECK(stretchFilter.apply(&sound) == true);
        CHECK(sound.getSamplesCnt() == 6);
    }

    SECTION("Lowpass filter check")
    {
        Waveform sound(5);
        std::vector<int16_t>& samples = sound.getSamples();
        samples[0] = 1;
        samples[1] = 2;
        samples[2] = 3;
        samples[3] = 2;
        samples[4] = 1;
        Lowpass lowpassFilter(3);
        CHECK(lowpassFilter.apply(&sound) == true);
        CHECK(samples[0] == 1);
        CHECK(samples[1] == 2);
        CHECK(samples[2] == 2);
        CHECK(samples[3] == 2);
        CHECK(samples[4] == 1);
    }
}