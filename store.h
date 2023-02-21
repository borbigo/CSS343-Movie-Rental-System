#ifndef STORE_H
#define STORE_H
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "movieinventory.h"
#include "classic.h"
#include "comedy.h"
#include "drama.h"
#include "customerdatabase.h"

class Store {
    public:
        //constructor
        Store();
        //constructor with inital store name
        Store(std::string &);

        //destructor
        ~Store();

        //reader functions
        void readMovies(std::string &);
        void readCommands(std::string &);
        void readCustomers(std::string &);
        
        //setter function
        void setStoreName(std::string &);

        //getter function
        std::string getStoreName();

        // custom string to int function
        static int cstoi(std::string &);
        
        //implements MovieInventory to keep track of
        //all movies held in store
        static MovieInventory StoreInventory;

        //removes whitespaces from before and after strings
        static std::string ltrim(const std::string &);
        static std::string rtrim(const std::string &);
        static std::string trim(const std::string &);
        
    private:
        static const string WHITESPACE;
        CustomerDatabase StoreCustomerDatabase;
        string storeName;
};


#endif // STORE_H
