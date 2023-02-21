/**
 Andrzej Dawiec and Bastien Orbigo
 CSS343  A Fall 2022
 Movies Project: comedy.h
 
comedy.h is the header file for the Comedy class, which implements
 the constructor and a destructor, inheriting from the Movie class.
 */
#ifndef COMEDY_H
#define COMEDY_H
#include <iostream>
#include "movie.h"

class Comedy : public Movie {
    public:
        //constructor
        Comedy(const int stock, const std::string director,
        const std::string title, const int year);
        
        //destructor
        ~Comedy();
};

#endif // COMEDY_H
