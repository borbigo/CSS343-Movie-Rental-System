/**
 Andrzej Dawiec and Bastien Orbigo
 CSS343 A Autumn 2022
 Movies Project:  classic.h
 
 classic.h is the header file for the Classic class, which implements
 the constructor and a destructor, inheriting from the Movie class.
 This class contains extra functions such as the getters and setters
 as the Classic movie objects utilize the major actor for sorting.
 */
#ifndef CLASSIC_H
#define CLASSIC_H
#include <iostream>
#include "movie.h"

using namespace std;

class Classic : public Movie {
    public:

        Classic();
        //constructor
        Classic(const int tStock, const std::string director,
        const std::string title, const std::string firstName, const std::string lastName,
        const int month, const int year);
        
        //destructor
        ~Classic();

        //getter functions
        std::string getActor(); //return actor name
        std::string getReleaseDate(); //return release date
        int getTotalStock();

        //setter functions
        void setTotalStock(int);

    private:
        std::string firstName;
        std::string lastName;
        int month;
        int totalStock;
};

#endif // CLASSIC_H
