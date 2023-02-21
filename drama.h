/**
 Andrzej Dawiec and Bastien Orbigo
 CSS343 A Fall 2022
 Movies Project: drama.h
 
 drama.h is the header file for the Drama class, which implements a constructor and a destructor,
 inheriting from the Movie class.
 */
#ifndef DRAMA_H
#define DRAMA_H
#include <iostream>
#include "movie.h"

class Drama : public Movie {
    public:
        //constructor
        Drama(const int stock, const std::string director, const std::string title, const int year);
        
        //destructor
        ~Drama();
};
#endif // DRAMA_H
