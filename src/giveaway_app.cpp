/*
File: giveaway_app.cpp

Brief: 

Author: Alexander DuPree

Date: 1/13/2019
*/

#include <random>
#include <chrono>
#include "giveaway_app.h"

using namespace clara;

/****** Static Definitions ******/

bool Giveaway_App::show_help = false;
bool Giveaway_App::version_request = false;
Giveaway_App::Contestants Giveaway_App::contestants = Contestants();

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
        display_winner(select_winner());
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

void Giveaway_App::display_winner(const std::string& winner) const
{
    for (int i = 0; i < 15; ++i)
    {
        std::cout << '\n';
    }

    std::cout << "\nThe contestants were: " << std::endl;
    for (auto contestant : contestants)
    {
        std::cout << contestant << std::endl;
    }

    std::cout << "\nCONGRATULATIONS!! " << winner << " WINS!!!";

    for (int i = 0; i < 10; ++i)
    {
        std::cout << '\n';
    }
    return;
}

const std::string& Giveaway_App::select_winner() const
{
    int winner = rand_index();
    for (const std::string& contestant : contestants)
    {
        if(winner-- <= 0)
        {
            return contestant;
        }
    }
    throw "Unable to select winner";
}

int Giveaway_App::rand_index() const 
{
    std::mt19937 generator(get_seed());
    std::uniform_int_distribution<int> u_dist(0, contestants.size() - 1);

    return u_dist(generator);
}

long long Giveaway_App::get_seed() const
{
    return std::chrono::high_resolution_clock::now().time_since_epoch().count();
}

