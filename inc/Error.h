//
// Created by lars on 05/11/16.
//

#ifndef BATTLESHIP_ERROR_H
#define BATTLESHIP_ERROR_H

#include <stdexcept>

class Error : public std::runtime_error
{
    Error ( const std::string& exeception )
            : runtime_error( exeception ) {}
};


#endif //BATTLESHIP_ERROR_H
