/**
 Andrzej Dawiec and Bastien Orbigo
 CSS343 A Autumn 2022
 Movies Project: comedy.h
 
 comedy.cpp implements the comedy.h by specifiying the constructor and using the functions such as
 setStock, setDirector, setTitle, setReleaseYear, and setGenre to create the Comedy movie project.
 */
#include "comedy.h"
#include <iostream>

//constructor
Comedy::Comedy(const int stock, const std::string director, const std::string title, const int year) {
    setStock(stock);
    setDirector(director);
    setTitle(title);
    setReleaseYear(year);
    setGenre("F");
}
    
Comedy::~Comedy() {};
