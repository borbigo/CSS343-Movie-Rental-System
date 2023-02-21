/**
 Andrzej Dawiec and Bastien Orbigo
 CSS343 A Autumn 2022
 Movies Project:  movieinventory.h
 
 movieinventory.h is the header file that defines both the MovieHash class and the MovieInventory class
 */
#ifndef HASTABLE_H
#define HASTABLE_H
#define SIZE 9999
#include "movie.h"
#include "classic.h"

/**
 MovieHash is used to hold a key value and a Movie/Classic object
 */
class MovieHash {
    public:
        int key;
        
        //implements Movie objects for hashtable
        Movie *movie;
        Classic *classic;
        bool isClassic;

        //default constructor, no arg
        MovieHash() {
            key = 0;
            movie = nullptr;
            classic = nullptr;
            isClassic = false;
        }

        //constuctor with key and Movie pair
        MovieHash(int k, Movie *movi) {
            key = k;
            movie = movi;
            isClassic = false;
        }

        //overloaded constructor specific for Classic movies
        MovieHash(int k, Classic *classics) {
            key = k;
            classic = classics;
            isClassic = true;
        }
};

/**
 MovieInventory hashes movies with a key, utilizing insert, search, and remove functions. Can also
 print the entire Movie database which prints its inventory
 */
class MovieInventory {
    public:
        //constructor
        MovieInventory();

        //destructor
        ~MovieInventory();

        //destructor helper function
        void destroy();

        //returns hashvalue of key
        int hashFunction(int key);

        //insert fucntions
        void insert(int key, Movie* moviePtr);
        void insert(int key, Classic* classicPtr);

        //search functions
        Movie* search(int key);
        Classic* classicSearch(int key);

        //remove and print inventory functions
        void remove(int key);
        void printInventory();

    private:
        MovieHash database[SIZE];
};

#endif // HASTABLE_H
