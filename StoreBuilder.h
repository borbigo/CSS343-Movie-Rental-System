/**
 Andrzej Dawiec and Bastien Orbigo
 CSS343 A Autumn 2022
 Movies Project: StoreBuilder.h
 
 StoreBuilder.h defines the StoreBuilder class which is used to create a store and adds the store to a vector
 of Store object pointers.
 */
#ifndef STOREBUILDER_H
#define STOREBUILDER_H
#include <vector>
#include "store.h"

class StoreBuilder {
    public:
        //constructor
        StoreBuilder();

        //destructor
        ~StoreBuilder();

        //initialize store
        void addStore(std::string &);

        //getter function
        Store* getStore(int);

    private:
        //tracks all the Stores created 
        std::vector<Store*> storeList;
};

#endif // STOREBUILDER_H
