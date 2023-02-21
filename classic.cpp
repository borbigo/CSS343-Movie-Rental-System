/**
 Andrzej Dawiec and Bastien Orbigo
 CSS343 A Autumn 2022
 Movies Project:  classic cpp
 
 classic.cpp implements the functions outlined in the classic.h header file to create Classic
 movie objects.
 */
#include "classic.h"
#include <iostream>

/**
 constructor
 */
Classic::Classic() {}

/**
 constructor takes a stock integer, the director name, the title, the first and last names of the major actor
 and the month and year for the release date.
 */
Classic::Classic(const int tStock, const std::string director, const std::string title, const std::string firstName, const std::string lastName, const int month, const int year) {
    this -> setTotalStock(tStock);
    this -> setStock(tStock);
    Movie::setDirector(director);
    Movie::setTitle(title);
    this -> firstName = firstName;
    this -> lastName = lastName;
    this -> month = month;
    Movie::setReleaseYear(year);
    Movie::setGenre("C");
}

/**
 destructor
 */
Classic::~Classic() {};

/**
 getActor() returns the name of the major actor
 */
std::string Classic::getActor() {
    return (firstName + " " + lastName);
}

/**
 getReleaseDate() returns the month and year that the movie was released
 */
std::string Classic::getReleaseDate() {
    return (to_string(month) + " " + to_string(getReleaseYear()));
}

/**
 setTotalStock() takes an integer value in and sets the total stock of the Classic movie to the
 argument value
 */
void Classic::setTotalStock(int in) {
    this -> totalStock = in;
}

/**
 getTotalStock() returns the integer value of the totalStock variable
 */
int Classic::getTotalStock() {
    return totalStock;
}
