/**
 Andrzej Dawiec and Bastien Orbigo
 CSS343 A Autumn 2022
 Movies Project:  customerdatabase.cpp
 
 customerdatabase.cpp implements the CustomerDatabase class outlined in the header file.
 */
#include "customerdatabase.h"
#include <iostream>

/**
 constructor: sets each spot in the database to an empty CustomerHash object, to be modified
 later with the hash value and Customer object
 */
CustomerDatabase::CustomerDatabase() {
	for (int i = 0; i < SIZE; i++) {
        database[i] = CustomerHash();
    }
}

/**
 Destructor utilizes a helper function destroy() to delete Customer objects
 */
CustomerDatabase::~CustomerDatabase() {
	destroy();
}

/**
 destroy() is a helper function for the destructor that loops through the entire database variable,
 checking if the customer at that spot is a nullptr, which if not nullptr, deletes it to free memory
 */
void CustomerDatabase::destroy() {
	for (auto i : database) {
		if (i.customer != nullptr) {
			delete i.customer;
		}
	}
}

/**
 hashFunction() takes an integer key value, and returns the hash by using the modulo operator
 to create a hash index by using the key input and the SIZE of the database table.
 */
int CustomerDatabase::hashFunction(int key) {
	int hash = SIZE;
	return key % hash;
}

/**
 insert() takes a key and a Customer pointer, which starts by hashing the key of the Customer,
 setting the isUnoccupied variable to true at first. If it doesn't surpass the SIZE of the database, it
 checks if the key  at that hashIndex = 0, inserting the account, otherwise, it checks if it's a duplicate account, deleting it if it is a duplicate.
 */
void CustomerDatabase::insert(int key, Customer *custPtr) {
	//hash the user id
	int hash = hashFunction(key);
	bool isUnoccupied = true;

	while (hash < SIZE) {
		if (hash == 0) {
			hash = 1;
		}
		if (database[hash].key == 0) {
			// inserts the account
			database[hash].key = hash;
			database[hash].customer = custPtr;
			return;
		}
		//check it's non duplicate account
		if (database[hash].customer -> getName() == custPtr -> getName()) {
			cout << "Duplicate accounts not allowed." << endl;
			delete custPtr;
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
 search() takes a key int value, hashes the key at first and checks if the spot at that hash isn't a
 nullptr and that the key is the ID, returning the customer if true, otherwise, increments the hash,
 updates the isUnoccupied variable. Returns an error message if it can't find the customer with that
 key.
 */
Customer* CustomerDatabase::search(int key) {
	int hash = hashFunction(key);
	bool isUnoccupied = true;

	while (hash < SIZE) {
		if (database[hash].customer != nullptr && database[hash].customer -> getID() == key) {
			return database[hash].customer;
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
 remove() takes a key variable and performs similar to the search and insert functions, checking the ID
 and its equivalence to the key, creating a temp Customer object, setting the database at that value to
 that temp value, overwriting whatever Customer was originally in that spot, otherwise, updates the
 isUnoccupied varible. Returns an error message if the key could not be found.
 */
void CustomerDatabase::remove(int key) {
	int hash = hashFunction(key);
	bool isUnoccupied = true;

	while (hash < SIZE) {
		if (database[hash].customer -> getID() == key) {
			Customer temp = Customer(0, "first", "last");
			Customer* tempPtr = &temp;
			database[hash].customer = tempPtr;
			return;
		}
		hash++;
		if (isUnoccupied && hash == SIZE) {
			hash = 0;
			isUnoccupied = false;
		}
	}
	
    cerr << "Error: could not find customer with ID of '" << key << endl;
}
