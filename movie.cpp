/**
 Andrzej Dawiec and Bastien Orbigo
 CSS343 A Autumn 2022
 Movies Project: movie.cpp
 
 movie.cpp implements the Movie class to be inherited from by the Classic, Drama, and Comedy classes,
 utilizing the majority of the functionalities outlined in this class
 */
#include "movie.h"
#include <iostream>
#include <fstream>

/**
 constructor, to be overloaded by other classes that inherit from this class
 */
Movie::Movie() {}

/**
 destructor
 */
Movie::~Movie() {}

/**
 overloaded operator == compares two Movies by comparing the category, title, director, and release year
 returning false if any are not equal, otherwise returns true
 */
bool Movie::operator==(Movie &movie) {
    if (this -> filmCategory != movie.filmCategory ||this -> title != movie.title || this -> director != movie.director || this -> year != movie.year) {
        return false;
    }
    return true;
}

/**
 overloaded operator != compares a Movie and checks if the movie is equivalent by using the overloaded
 operator ==
 */
bool Movie::operator!=(Movie &movie) {
    return !(*this == movie);
}

/**
 getter, returns stock of Movie
 */
int Movie::getStock() {
    return stock;
}

/**
 getter, returns title of Movie
 */
std::string Movie::getTitle() {
    return title;
}

/**
 getter, returns director of Movie
 */
std::string Movie::getDirector() {
    return director;
}

/**
 getter, returns release year of movie
 */
int Movie::getReleaseYear() {
    return year;
}

/**
 getter, returns genre of movie
 */
std::string Movie::getGenre() {
    return filmCategory;
}

/**
 setter, sets stock of the Movie
 */
void Movie::setStock(const int stock) {
    this -> stock = stock;
}

/**
 setter, sets title of the Movie
 */
void Movie::setTitle(const std::string title) {
    this -> title = title;
}

/**
 setter, sets director of the Movie
 */
void Movie::setDirector(const std::string director) {
    this -> director = director;
}

/**
 setter, sets release year of the Movie
 */
void Movie::setReleaseYear(const int year) {
    this -> year = year;
}

/**
 setter, sets genre of the Movie
 */
void Movie::setGenre(const std::string genre) {
    this -> filmCategory = genre;
}
