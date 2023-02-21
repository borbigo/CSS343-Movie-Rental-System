/**
 Andrzej Dawiec and Bastien Orbigo
 CSS343 A Autumn 2022
 Movies Proejct: movie.h
 
 movie.h is the header file for the Movie class, which is used by inheritance for the Classic, Drama, and
 Comedy classes.
 */
#ifndef MOVIE_H
#define MOVIE_H
#include <iostream>
#include <fstream>

class Movie {
    public:
        //default constructor, overloaded by each genre class
        Movie();

        //destructor
        virtual ~Movie();

        //overloaded comparison operators
        bool operator==(Movie &);
        bool operator!=(Movie &);
        friend std::ostream& operator<<(std::ostream& out, Movie&);

        //getter functions
        virtual int getStock();
        virtual std::string getTitle();
        virtual std::string getDirector();
        virtual int getReleaseYear();
        virtual std::string getGenre();

        //setter functions
        virtual void setStock(const int stock);
        virtual void setTitle(const std::string title);
        virtual void setDirector(const std::string director);
        virtual void setReleaseYear(const int year);
        virtual void setGenre(const std::string genre);
    
    private:
        std::string filmCategory;
        int stock;
        std::string director;
        std::string title;
        int year;
};

#endif // MOVIE_H
