/**
 Andrzej Dawiec and Bastien Orbigo
 CSS343  A Fall 2022
 Movies Project: customer.cpp
 
 customer.cpp implements the functionalities outlined in the header file,
 customer.h
 */
#include "customer.h"
#include "store.h"
#include <iostream>
#include <sstream>
#include <vector>

/*
 Overloaded operator << prints customer name to the console
 */
ostream& operator <<(ostream& out, Customer &rhs) {
    out << rhs.getName();
    return out;
}

/*
Overloaded operator == takes another Customer and checks if the ID and names
 are the same between two customers, returning either true/false.
 */
bool Customer::operator == (Customer &rhs) {
    return (this -> getID() == rhs.getID()) && (this -> getName() == rhs.getName());
}

/*
 Customer constructor takes an int value for the ID, and two strings,
 one for the first name, one for the last
 */
Customer::Customer(int id, std::string first , std::string last) {
    setID(id);
    setName(first, last);
}

/**
 Destructor
 */
Customer::~Customer() {};

/*
 setName() takes two strings, one first name, one last name, and sets it
 to the class variables
 */
void Customer::setName(std::string first, std::string last) {
    this -> firstName = first;
    this -> lastName = last;
}

/*
 setName() takes one full string name (containing both the first and last
 name within a single string. Uses a stringstream to input the firstName and
 lastName
 */
void Customer::setName(std::string name) {
    std::stringstream s(name);
    s >> firstName >> lastName;
}

/*
 setID takes an int number and sets the id to the argument value
 */
void Customer::setID(int number) {
    this -> id = number;
}

/*
 getName() returns the firstName + lastName
 */
std::string Customer::getName() {
    return firstName + " " + lastName;
}

/*
 getID() returns the customer's ID
 */
int Customer::getID() {
    return id;
}

/*
 addMovie() takes a Movie object and pushes it back into the vector that
 tracks the movies the customer currently has rented
 */
void Customer::addMovie(Movie &movie) {
    currentMovies.push_back(movie);
}

/*
 borrowMovie() checks the genre if it's a Comedy or Classic and creates a
 string to hold the genre, title, and year or genre, director, and title
 depending on the genre. From there, it generates a key using a custom
 string to int function and then performs a check to see if the movie A)
 exists and B) is in stock. If it is, it creates an error message and
 pushes that onto the transactionHistory.
 Otherwise, it adds the movie, searches the StoreInventory by the key,
 reduces the stock by 1, and prints a message to store in the
 transactionHistory.
 */
void Customer::borrowMovie(Movie &movie) {
    int key;
    std::string temp;
    
    if (movie.getGenre() == "F") {
        temp = "F" + movie.getTitle() + to_string(movie.getReleaseYear());
        key = Store::cstoi(temp);
    } else {
        temp = "D" + movie.getDirector() + movie.getTitle();
        key = Store::cstoi(temp);
    }
    
    //check if movie A) exists and B) is in stock
    if (Store::StoreInventory.search(key) == nullptr || Store::StoreInventory.search(key) -> getStock() == 0) {
        std::string errorM = to_string(movie.getReleaseYear()) + " " + movie.getTitle() + " is unavailable.";
        transactionHistory.push_back(errorM);
    } else {
        addMovie(movie);
        //finds movie to update the inventory
        Store::StoreInventory.search(key) -> setStock(Store::StoreInventory.search(key) -> getStock() - 1);
        std::string message = getName() + " borrowed: " + to_string(movie.getReleaseYear())+ " " + movie.getTitle();
        transactionHistory.push_back(message);
    }
}

/*
 borrowMovie() is an overloaded version of the same function, specific to
 Classic movies. It performs the same checks and uses the custom string
 to int to generate a key, then stores either a success or error
 transaction message in the transactionHistory
 */
void Customer::borrowMovie(Classic &movie) {
    int key;
    std::string temp;
    std::string releasedate = movie.getReleaseDate();
    std::string acto = movie.getActor();
    temp = "C" + releasedate + acto;
    key = Store::cstoi(temp);
    
    //check if movie A) exists and B) is in stock
    if (Store::StoreInventory.classicSearch(key) == nullptr || Store::StoreInventory.classicSearch(key) -> getStock() == 0) {
        std::string errorM = to_string(movie.getReleaseYear())  + " " + movie.getTitle() + " is unavailable.";
        transactionHistory.push_back(errorM);
    } else {
        addMovie(movie);
        //finds movie to update the inventory
        Store::StoreInventory.classicSearch(key) -> setStock(Store::StoreInventory.classicSearch(key) -> getStock() - 1);
        std::string message = getName() + " borrowed: " + to_string(movie.getReleaseYear()) + " " + movie.getTitle();
        transactionHistory.push_back(message);
    }
}

/*
 returnMovie() takes a Movie object and loops through the currentMovies
 which tracks the movies checked out, looking for an equivalent movie by
 using an iterator. If it finds the movie as checked out, it changes
 movieBorrowed to true. If false, it generates a message which is pushed on
 the transactionHistory and otherwise checks the genre and builds a string
 around it, generating a key, which searches for the movie in the system
 and updates the inventory. Finally, it creates a success return message
 which is pushed onto the transactionHistory.
 */
void Customer::returnMovie(Movie &movie) {
    //used to check if the customer actually has it checked out
    bool movieBorrowed = false;
    
    for (int i = 0; i < currentMovies.size(); i++) {
        if (currentMovies.at(i) == movie) {
            std::vector<Movie>::iterator it;
            it = currentMovies.begin() + i;
            currentMovies.erase(it);
            movieBorrowed = true;
        }
    }

    //prints error if not borrowed
    if (movieBorrowed == false) {
        string errorM = to_string(movie.getReleaseYear()) + " " +movie.getTitle() + " is not borrowed by " + getName();
        transactionHistory.push_back(errorM);
    } else { //performs return
        string temp;
        if (movie.getGenre() == "F") {
            temp = "F" + Store::trim(movie.getTitle()) + to_string(movie.getReleaseYear());
        }
        if (movie.getGenre() == "D") {
            temp = "D" + Store::trim(movie.getDirector()) + Store::trim(movie.getTitle());
        }
        
	    int key = Store::cstoi(temp);
        //finds movie to update the inventory
        Store::StoreInventory.search(key) -> setStock(Store::StoreInventory.classicSearch(key) -> getStock() + 1);
        std::string message = getName() + " returned: " + to_string(movie.getReleaseYear()) + " " + movie.getTitle();
        transactionHistory.push_back(message);    
    }
}

/*
 returnMovie() is overloaded for Classic movies, performing the same
 functions with extra data as the two other genres of movies.
 */
void Customer::returnMovie(Classic &movie) {
    //used to check if the customer actually has it checked out
    bool movieBorrowed = false;
    
    for (int i = 0; i < currentMovies.size(); i++) {
        if (currentMovies.at(i) == movie) {
            std::vector<Movie>::iterator it;
            it = currentMovies.begin() + i;
            currentMovies.erase(it);
            movieBorrowed = true;
        }
    }

    //if not in customer inventory, print error
    if (movieBorrowed == false) {
        std::string errorM = to_string(movie.getReleaseYear()) + " " + movie.getTitle() + " is not in borrowed by " + getName();
        transactionHistory.push_back(errorM);
    } else { //performs return
        std::string temp;
        
        temp = "C" + movie.getReleaseDate() + movie.getActor();

	    int key = Store::cstoi(temp);
        //finds movie to update the inventory
        Store::StoreInventory.classicSearch(key) -> setStock(Store::StoreInventory.classicSearch(key) -> getStock() + 1);
        std::string message = getName() + " returned: " + to_string(movie.getReleaseYear()) + " " + movie.getTitle();
        transactionHistory.push_back(message);    
    }
}

/*
 printHistory() loops through the Customer's transactionHisory() and
 prints out the history stored at all the different indices. 
 */
void Customer::printHistory() {
    for (int i = 0; i < transactionHistory.size(); i++) {
        int ind = (int) i;
        cout << transactionHistory.at(ind) << endl;
    }
}
