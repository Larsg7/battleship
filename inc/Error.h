#ifndef BATTLESHIP_ERROR_H
#define BATTLESHIP_ERROR_H

#include <stdexcept>

/**
 * Short class to report errors
 */
class Error : public std::runtime_error
{
public:
    Error ( const std::string& exeception )
            : runtime_error( exeception ) {}
};


#endif //BATTLESHIP_ERROR_H
