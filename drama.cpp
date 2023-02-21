/**
 Andrzej Dawiec and Bastien Orbigo
 CSS343  A Fall 2022
 Movies Project: drama.cpp
 
 drama.cpp implements the constructor and destructor outlined in the drama.h header file.
 This class inherits from the movie class, sharing many of the same functionalities through
 inheritance. 
 */

#include "drama.h"
#include <iostream>

/**
 Constructor takes an integer stock, a string director, a string title, and an int year value.
 Drama sorts by Director, then Title. It uses the Movie methods such as setStock, setDirector,
 setTitle, setReleaseYear, and setGenre to build the Drama object.
 */
Drama::Drama(const int stock, const std::string director, const std::string title, const int year) {
    Movie::setStock(stock);
    Movie::setDirector(director);
    Movie::setTitle(title);
    Movie::setReleaseYear(year);
    Movie::setGenre("D");
}

/**
 Destructor
 */
Drama::~Drama() {};
