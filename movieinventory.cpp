/**
 Andrzej Dawiec and Bastien Orbigo
 CSS343 A Autumn 2022
 Movies Project: movieinventory.cpp
 
 movieinventory.cpp implements the MovieInventory class outlined in the header file, movieinventory.h
 utilizing the MovieHash class.
 */
#include "movieinventory.h"
#include "store.h"
#include <iostream> 

/**
 constructor, loops through the database and sets it to a nullptr MovieHash object
 */
MovieInventory::MovieInventory() {
	for (int i = 0; i < SIZE; i++) {
        database[i] = MovieHash();
    }
}

/**
 destructor, utilizes a helper function, destroy()
 */
MovieInventory::~MovieInventory() {
	destroy();
}

/**
 destory() loops through the entire database, checking if the Movie or Classic object
 aren't nullptr, deleting the object if not nullptr
 */
void MovieInventory::destroy() {
	for (auto i : database) {
		if (i.movie != nullptr) {
			delete i.movie;
		}
		if (i.classic != nullptr) {
			delete i.classic;
		}
	}
}

/**
 hashFunction() takes a key, and returns the modified value by using the modulo operator with the key
 and the SIZE of the database
 */
int MovieInventory::hashFunction(int key) {
	int modVal = SIZE;
	return key % modVal;
}

/**
 insert() takes a key and a Movie pointer, hashes the key and then inserts the movie, so long as the
 key at the hash is 0, otherwise increments the hash and updates the isUnoccupied variable.
 */
void MovieInventory::insert(int key, Movie *moviPtr) {
	//hash the movie key
	int hash = hashFunction(key);
	bool isUnoccupied = true;

	while (hash < SIZE) {
		if (hash == 0) {
			hash = 1;
		}
		if (database[hash].key == 0) {
            // inserts the movie
            database[hash].key = hash;
            database[hash].movie = moviPtr;
            return;
        }

		hash++; 
		
		if (isUnoccupied && hash == SIZE) {
			hash = 1;
			isUnoccupied = false;
		}
	}
}

/**
 insert() is overloaded specifically for Classic objects, but performs similar to the insert() function for
 Movie objects. This insert function requires more checks of equivalence, to see if the movie is
 identical, incrementing stock if it is, otherwise, it creates a newTotal, updates the hash and modifies
 the isUnoccupied bool variable.
 */
void MovieInventory::insert(int key, Classic* classicPtr) {
    //hash the movie ID
    int hash = hashFunction(key);
    bool isUnoccupied = true;

    while (hash < SIZE) {
        if (hash == 0) {
            hash = 1;
        }
        if (database[hash].key == 0) {
            // inserts the account
            database[hash].key = hash;
            database[hash].classic = classicPtr;
            database[hash].isClassic = true;
            return;
        }

        if (database[hash].isClassic) {
            if (database[hash].classic -> getTitle() == classicPtr -> getTitle()) {
                if (database[hash].classic -> getActor() == classicPtr -> getActor()) {
                    if (database[hash].classic -> getReleaseDate() == classicPtr -> getReleaseDate()) {
                        //identical movie gets it stock incremented
                        database[hash].classic -> setStock(database[hash].classic -> getStock() + classicPtr -> getStock());
                        return;
                    }
                }
                int newTotal = database[hash].classic -> getStock() + classicPtr -> getStock();
                database[hash].classic -> setTotalStock(newTotal);
                classicPtr -> setTotalStock(newTotal);
            }
        }
        
        hash++;
        if (isUnoccupied && hash == SIZE) {
            hash = 1;
            isUnoccupied = false;
        }
    }
}

/**
 printInventory() loops through the database, checking if the key is not equal to 0. From there, it checks
 if it's a Classic, printing the title and stock, otherwise prints the title and stock using the normal Movie
 functions
 */
void MovieInventory::printInventory() {
	for(int i = 0; i < SIZE; i++) {
		if (database[i].key != 0) {
			if (database[i].isClassic) {
				cout << database[i].classic -> getTitle() << " " <<
				database[i].classic -> getStock() << endl;
			} else {
				cout << database[i].movie -> getTitle() << " " <<
				database[i].movie -> getStock() << endl;
			}
		}
	}
}

/**
 search() takes a key value, searches the database by hash and checks if the key is 0, printing an
 error message, meaning the movie isn't in the database, otherwise, it checks the genres and
 retruns the movie at the hash and updates the hash and isUnoccupied variable. Prints an error message
 if the Movie could not be found
 */
Movie* MovieInventory::search(int key) {
	
	int hash = hashFunction(key);
	bool isUnoccupied = true;

	while (hash < SIZE) {
		if(database[hash].key == 0) {
			cerr << "Movie not in Database" << endl;
			break;
		}
		if (database[hash].isClassic) {
			hash++;
			continue;
		}
		if (database[hash].movie -> getGenre() == "F") { //comedy
			if (database[hash].key == hash) {
				return database[hash].movie;
			}
		} else if (database[hash].movie -> getGenre() == "D") { //drama
			if (database[hash].key == hash) {
				return database[hash].movie;
			}
		}
		hash++;
		if (isUnoccupied && hash == SIZE) {
			hash = 0;
			isUnoccupied = false;
		}
	}
	
	cerr << "Error: could not find Movie with Key of '" << key << endl;
	return nullptr;
}

/**
 classicSearch() is a modified search() function, specifically implemented for only Classic objects. It runs
 the same checks and updates the hash and returns the Classic object the same as a normal movie.
 */
Classic* MovieInventory::classicSearch(int key) {
	
	int hash = hashFunction(key);
	
	bool isUnoccupied = true;

	while (hash < SIZE) {
		
		if (!(database[hash].isClassic)) {
			hash++;
			continue;
		}
		if (database[hash].classic -> getGenre() == "C") { //classic
			if (hash == database[hash].key) {
				return database[hash].classic;
			}
		}

		hash++;
		if (isUnoccupied && hash == SIZE) {
			hash = 0;
			isUnoccupied = false;
		}

	}

	cerr << "Error: could not find customer with ID of '" << key << endl;
	return nullptr;
}

/**
 remove() takes a key value, and checks if the movie at that hash from the key is a specific kind, creating a
 blank, temp Movie/Classic object, then sets the hash point to that blank object, overwriting the previous
 object in its place.
 */
void MovieInventory::remove(int key) {
	int hash = hashFunction(key);
	bool isUnoccupied = true;

	while (hash < SIZE) {
		if (database[hash].movie -> getGenre() == "F") { //comedy
			if (database[hash].key == key) {
				Movie temp = Movie();
				Movie* tempPtr = &temp;
				database[hash].movie = tempPtr;
				return;
			}
		} else if (database[hash].movie -> getGenre() == "D") { //drama
			if (database[hash].key == key) {
				Movie temp = Movie();
				Movie* tempPtr = &temp;
				database[hash].movie = tempPtr;
				return;
			}
		} else if (database[hash].movie -> getGenre() == "C") { //classic
			if (database[hash].key == key) {
				Classic temp = Classic();
				Classic* tempPtr = &temp;
				database[hash].classic = tempPtr;
				return;
			}
		}
		hash++;
		if (isUnoccupied && hash == SIZE) {
			hash = 0;
			isUnoccupied = false;
		}
	}
	
    cerr << "Error: could not find customer with ID of '" << key << endl;
}

