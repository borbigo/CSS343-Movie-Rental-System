/**
 Andrzej Dawiec and Bastien Orbigo
 CSS343  A Fall 2022
 Movies Project: customer.h
 
 customer.h is the header file for the Customer class, defining the constructor and destructor, the setter
 functions such as setName and setID which allow modifications to the customer name and ID number, the getters for those data values, an add function to add to their transaction history, borrow and return functions, a printHistory() function to print the transaction history and overloaded operators.
 */
#ifndef CUSTOMER_H
#define CUSTOMER_H
#include <iostream>
#include <vector>
#include "classic.h"
#include "movieinventory.h"

class Customer {
    public:
        //constructor
        Customer(int, std::string, std::string);
        
        //destructor
        ~Customer();

        //setter functions
        //first and last name
        void setName(std::string, std::string);
        //full name as one string
        void setName(std::string);
        void setID(int);
        
        //getter functions
        std::string getName();
        int getID();

        //adds movie to transaction history
        void addMovie(Movie &);

        //borrows a movie and logs in transaction history
        void borrowMovie(Movie &);
        void borrowMovie(Classic &);

        //returns a movie and logs in transaction history
        void returnMovie(Movie &);
        void returnMovie(Classic &);

        //prints full customer transaction history
        void printHistory();

        //overloaded operators
        friend ostream& operator << (ostream& out, Customer &rhs);
        bool operator == (Customer &);

    private:
        int id;
        std::string firstName;
        std::string lastName;
        //tracks current movies rented
        std::vector<Movie> currentMovies;
        //tracks full transaction history
        std::vector<std::string> transactionHistory;
};

#endif // CUSTOMER_H
