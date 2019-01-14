/* File: giveaway.cpp
 *
 * Brief: Command-Line applcation that selects a winner from a list of contestants
 *
 * Author: Alexander DuPree
 *
 * Date: 1/9/2019
*/

#include "giveaway_app.h"

int main(int argc, char ** argv) 
{
    int return_code = 0;
    try
    {
        Giveaway_App app(argc, argv);

        return_code = app.run();
    }
    catch(const clara::detail::InternalParseResult& err)
    {
        std::cerr << "Parser Error: " << err.errorMessage() << std::endl;
        return_code = 1;
    }
    catch(const char* err)
    {
        std::cerr << err << std::endl;
        return_code = 1;
    }
    
    return return_code;
}

