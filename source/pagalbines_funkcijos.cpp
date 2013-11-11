#include "pagalbines_funkcijos.h"
#include <string>
	using namespace std;

void remove_carriage_return(std::string& line)
{
    if (*line.rbegin() == '\r')
    {
        line.erase(line.length() - 1);
    }
}