/*
File: giveaway_app.h

Brief: 

Author: Alexander DuPree

Date: 1/13/2019
*/

#ifndef GIVEAWAY_APP_H
#define GIVEAWAY_APP_H

#define GIVEAWAY_VERSION "giveaway v1.0.0"

#include <list>
#include <iostream>
#include <clara.hpp>

class Giveaway_App 
{
  public:

    typedef std::vector<std::string> Contestants;
     
    Giveaway_App(int argc, char** argv);

    // Overloaded constructor is used for unit tests and isn't needed in production
    Giveaway_App(int argc, const char** argv);

    int run() const;

    void usage() const;

    void version() const;

    const std::string& select_winner() const;

    void display_winner(const std::string& winner) const;

  private:

    int rand_index() const;
    long long get_seed() const;

    static bool show_help;
    static bool version_request;
    static Contestants contestants;

    static const clara::Parser parser;
};

#endif // GIVEAWAY_APP_H

