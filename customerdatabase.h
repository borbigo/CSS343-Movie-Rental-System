/**
 Andrzej Dawiec and Bastien Orbigo
 CSS343 A Autumn 2022
 Movies Project:  customerdatabase.h
 
 This file outlines the functions needed for the CustomerHash class and the CustomerDatabase
 class.
 */
#ifndef CUSTOMERDATABASE_H
#define CUSTOMERDATABASE_H
#define SIZE 9999
#include "customer.h"

/**
 CustomerHash is used to hold a key value and a Customer object when hashed.
 */
class CustomerHash {
    public:
        int key;
        
        //Customer object for hashtable
        Customer *customer;
        
        //default constructor, no arg
        CustomerHash() {
            key = 0;
            customer = nullptr;
        }

        //constuctor with key and Customer
        CustomerHash(int k, Customer *cust) {
            key = k;
            customer = cust;
        }
};

/**
 CustomerDatabase utilizes the CustomerHash class to hash Customers to a custom implemented
 HashTable, inserting, searching, and removing Customers.
 */
class CustomerDatabase {
    public:
        //constructor
        CustomerDatabase();

        //destructor
        ~CustomerDatabase();

        //destructor helper function
        void destroy();

        //returns hashvalue of key
        int hashFunction(int key);

        //search for, insert, and remove customers from database
        void insert(int key, Customer *custPtr);
        Customer* search(int key);
        void remove(int key);

    private:
        CustomerHash database[SIZE];
};

#endif // CUSTOMERDATABASE_H
