/*
File: giveaway_app.cpp

Brief: 

Author: Alexander DuPree

Date: 1/13/2019
*/

#include "giveaway_app.h"

using namespace clara;

/****** Static Definitions ******/

static bool Giveaway_App::show_help = false;
static Giveaway_App::Contestants Giveaway_App::contestants = Contestants();

const Parser Giveaway_App::parser = 
         Opt(version_request)
            ["-V"]["--version"]("Show version and quit") |
         Arg(contestants, "Contestants")("Single token strings of the contestants") |
         Help(show_help);

/********************************/

Giveaway_App::Giveaway_App(int argc, char** argv)
{
    auto result = parser.parse(Args(argc, argv));

    // Options failed to parse
    if(!result)
    {
        throw result;
    }
}

Giveaway_App::Giveaway_App(int argc, const char** argv)
    : Giveaway_App(argc, const_cast<char**>(argv)) {}

int Giveaway_App::run() const
{
    if(show_help)
    {
        usage();
    }
    else if(version_request)
    {
        version();
    }
    else
    {
        std::cout << contestants << std::endl;
        //display_temp_conversion();
    }
    return 0;
}

void Giveaway_App::usage() const
{
    std::cout 
    << "\nSimple command line application that randomly selects a winner from a list of names\n";

    parser.writeToStream(std::cout);
    
    std::cout << '\n' << std::endl;
    return;
}

void Giveaway_App::version() const
{
    std::cout << GIVEAWAY_VERSION << std::endl;
    return;
}

