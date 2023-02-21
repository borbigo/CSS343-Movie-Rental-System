/**
 Andrzej Dawiec and Bastien Orbigo
 CSS343 A Autumn 2022
 Movies Project: driver.cpp
 
 driver.cpp is the driver of the entire project, consisting of only the main method, which consists of four
 phases: a build phase in which the intitial store is created and three phases to read in the three text
 files - customers, movies, and commands.
 */
#include <iostream>
#include "store.h"
#include "StoreBuilder.h"

int main() {
    /**
     PHASE 1: Building store
     */
    cout << "Attempting to build store: " << endl;
    //initliaze store
    StoreBuilder sBuilder;
    std::string storeName = "store0";
    sBuilder.addStore(storeName);
    cout << "Store successfully created!" << endl << endl;
    
    /**
    PHASE 2: READING IN CUSTOMERS
     */
    cout << "Attempting to read-in and build customer database: " << endl;
    //read customers from txt file and initialize
    std::string customerFile = "data4customers.txt";
    sBuilder.getStore(0) -> readCustomers(customerFile);
    cout << "Customer database created!" << endl << endl;
    
    /**
     PHASE 3: READING IN MOVIES
     */
    cout << "Attempting to read-in and build movie database: " << endl;
    //read movies from txt file and initalize
    std::string moviesFile = "data4movies.txt";
    sBuilder.getStore(0) -> readMovies(moviesFile);
    cout << "Movie database created!" << endl << endl;
    
    /**
     PHASE 4: READING IN COMMANDS
     */
    cout << "Attempting to run customer commands: " << endl;
    //read commands from txt file and initialize
    std::string commandsFile = "data4commands.txt";
    sBuilder.getStore(0) -> readCommands(commandsFile);
    cout << "Commands successfully completed!" << endl << endl;
    
    cout << "Store is fully operational! " << endl;
}

