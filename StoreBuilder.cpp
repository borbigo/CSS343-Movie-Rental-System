/**
 Andrzej Dawiec and Bastien Orbigo
 CSS343 A Autumn 2022
 Movies Project: StoreBuilder.cpp
 
 StoreBuilder.cpp implements the StoreBuilder class, consisting of a constructor, destructor, an add
 and a getter.
 */
#include "StoreBuilder.h"

/**
 constructor
 */
StoreBuilder::StoreBuilder() {}

/**
 destructor, runs through the storeList vector, deleting the Store pointer at each index
 */
StoreBuilder::~StoreBuilder() {
    for(auto i : storeList) {
        delete i;
    }
}

/**
 addStore() takes a string name and pushes back a new Store object with the name passed in
 */
void StoreBuilder::addStore(std::string &name) {
    storeList.push_back(new Store(name));
}

/**
 getStore() gets a storeID integer and returns the Store at that index 
 */
Store* StoreBuilder::getStore(int storeID) {
    return storeList.at(storeID);
}
