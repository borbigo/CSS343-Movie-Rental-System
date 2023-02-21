#include "store.h"
#include "customer.h"
#include <iostream>
#include <algorithm>
#include <string>
#include <iostream>
#include <cstddef>

//initialize MovieInventory object
MovieInventory Store::StoreInventory;

const std::string Store::WHITESPACE =  " \n\r\t\f\v";

Store::Store() {}

Store::~Store() {}

Store::Store(std::string &theName) {

    this -> storeName = theName;
}

std::string Store::getStoreName() {
    return storeName;
}

int Store::cstoi(std::string & in) {
    int sum = 0;
    for (int i{0};  i < in.length(); i++) {
        sum += in[i];
    }
    return sum;
}

void Store::readMovies(std::string &fileName) {
    std::string line;
    std::string director;
    std::string title;
    std::string firstName;
    std::string lastName;
    int classicMonth;
    int classicYear;
    std::string currentMovie = "";
    std::vector<std::string> v;
    ifstream data;
    data.open(fileName);
    if (!data) {
        cerr << "Error: file '" << fileName << "' could not be opened" << endl;
        exit(1);
    }

    while (!data.eof()){
        v.clear();
        std::string substr;
        stringstream iss;
        getline(data, line);
        iss << line;
        while (getline(iss, substr, ',')) {
            v.push_back(trim(substr));
        }
        
        if (line == "") {
            break;
        }
        
        currentMovie = v[0];
        stringstream ss(v[4]);
        switch((int)currentMovie[0]) {
            case 67: { //C
                ss >> firstName;
                ss >> lastName;
                ss >> classicMonth;
                ss >> classicYear;
                v[1] = trim(v[1]);
                std::string toStock = v[1];
                int actualStock = stoi(toStock);
                Classic *classics = new Classic(actualStock, v[2], v[3], firstName, lastName, classicMonth, classicYear);
                std::string keyC = "C" + to_string(classicMonth) + " " + to_string(classicYear) + firstName + " " + lastName;
                int cKey = cstoi(keyC);
                Store::StoreInventory.insert(cKey, classics);
            }
                break;
            case 68: { //D
                Drama *dramas = new Drama(stoi(v[1]), v[2], v[3], stoi(v[4]));
                std::string keyD = "D" + v[2] + v[3];
                int Dkey = cstoi(keyD);
                Store::StoreInventory.insert(Dkey, dramas);
            }
                break;
    
            case 70: { //F
                Comedy *comedies = new Comedy(stoi(v[1]), v[2], v[3], stoi(v[4]));
                std::string keyF = "F" + v[3] + v[4];
                int Fkey = cstoi(keyF);
                Store::StoreInventory.insert(Fkey, comedies);
            }
                break;
            default: {
                cerr << "Error: invalid movie type '" << currentMovie[0] << "'" << endl;
                break;
            }
        }
    }
}

void Store::readCommands(std::string &fileName) {
    std::string currentCommand = "";
    std::string customerID;
    std::string mediaType;
    std::string movieType;
    std::string movieData;
    std::string line;
    
    ifstream data;

    std::vector<std::string> v;
    data.open(fileName);
    
    if (!data) {
        cerr << "Error: file '" << fileName << "' could not be opened" << endl;
        exit(1);
    }
    
    while (!data.eof()) {
        v.clear();
        getline(data, line);
        stringstream iss;
        iss << line;
        std::string substr;
        
        while (iss >> substr) {
            v.push_back(trim(substr));
        }
        
        currentCommand = v[0];
        switch((int)currentCommand[0]) {
            case 66: { //B
                customerID = v[1];
                mediaType = v[2];
                if (mediaType != "D") {
                    cerr << "Error: invalid media type '" << mediaType << "'" << endl;
                } else {
                    movieType = v[3];
                    if (movieType == "F") { //Comedy
                        std::string title;
                        std::string releaseYear;
                        
                        int last = v.size();
                        for (int i{4}; i < v.size() - 1; i++) {
                            if (i < v.size() - 2) {
                                title.append(v[i] + " ");
                            } else {
                                std::string lastVal = v[i];
                                lastVal.erase(remove(lastVal.begin(), lastVal.end(), ','), lastVal.end());
                                title.append(lastVal);
                            }
                        }
                        releaseYear = v[last-1];
                        std::string key = "F" + trim(title) + releaseYear;
                        
                        Customer* cust = Store::StoreCustomerDatabase.search(stoi(customerID));
                        Movie* movie = StoreInventory.search(cstoi(key));
                        if (movie == nullptr || cust == nullptr) {
                            break;
                        }
                        cust -> borrowMovie(*movie);
                    } else if (movieType == "D") { //Drama
                        char ch = ',';
                        size_t found;
                        std::string director;
                        std::string toAdd;
                        int i{4};
                        do {
                            toAdd = v[i] + " ";
                            director.append(toAdd);
                            found = v[i].find_last_of(ch);
                            if (found != std::string::npos) {
                                break;
                            }
                            i++;
                        } while ((true));
                        
                        director.erase(remove(director.begin(), director.end(), ','), director.end());
                        director = trim(director);
                        std::string title;
                        i++;
                        int x = i;
                        for (int i = x; i < v.size(); i++) {
                            if (i < v.size() - 1) {
                                title.append(v[i] + " ");
                            } else {
                                std::string lastVal = v[i];
                                lastVal.erase(remove(lastVal.begin(), lastVal.end(), ','), lastVal.end());
                                title.append(lastVal);
                            }
                        }
                        std::string key = "D" + trim(director) + trim(title);
                        Customer* cust = Store::StoreCustomerDatabase.search(stoi(customerID));
                        Movie* movie = StoreInventory.search(cstoi(key));
                        if (movie == nullptr || cust == nullptr) {
                            break;
                        }
                        cust -> borrowMovie(*movie);
                    } else if (movieType == "C") { //Classic
                        std::string month;
                        std::string year;
                        std::string firstName;
                        std::string lastName;

                        month = v[4];
                        year = v[5];
                        firstName = v[6];
                        lastName = v[7];
                        std::string key = "C" + month + " " + year + firstName + " " + lastName;
                        Customer* cust = Store::StoreCustomerDatabase.search(stoi(customerID));
                        int ccKey = cstoi(key);
                        Classic* classicPtr = StoreInventory.classicSearch(ccKey);
                        if (classicPtr == nullptr || cust == nullptr) {
                            break;
                        }
                        cust -> borrowMovie(*classicPtr);
                    } else {
                        cerr << "Error: invalid movie type '" << movieType << "'" << endl;
                    }
                }
            }
                break;
            case 72: { //H
                customerID = v[1];
                Store::StoreCustomerDatabase.search(stoi(customerID)) -> printHistory();
            }
                break;
            case 73: { //I
                Store::StoreInventory.printInventory();
            }
                break;
            case 82: { //R
                customerID = v[1];
                mediaType = v[2];
                if (mediaType != "D") {
                    cerr << "Error: invalid media type '" << mediaType << "'" << endl;
                } else {
                    movieType = v[3];
                    if (movieType == "F") { //Comedy
                        std::string title;
                        std::string releaseYear;
                        int last = v.size();
                        for (int i{4}; i < v.size() - 1; i++){
                            if (i < v.size() - 2) {
                                title.append(v[i] + " ");
                            } else {
                                std::string lastVal = v[i];
                                lastVal.erase(remove(lastVal.begin(), lastVal.end(), ','), lastVal.end());
                                title.append(lastVal);
                            }
                        }
                        releaseYear = v[last-1];
                        std::string key = "F" + trim(title) + releaseYear;
                        Customer* cust = Store::StoreCustomerDatabase.search(stoi(customerID));
                        Movie* movie = Store::StoreInventory.search(cstoi(key));
                        cust -> returnMovie(*movie);
                    } else if (movieType == "D") { //Drama
                        char ch = ',';
                        size_t found;
                        std::string director;
                        std::string toAdd;
                        int i{4};
                        do {
                            toAdd = v[i] + " ";
                            director.append(toAdd);
                            
                            found = v[i].find_last_of(ch);
                            if (found != std::string::npos) {
                                break;
                            }
                            i++;
                        } while ((true));
                        
                        director.erase(remove(director.begin(), director.end(), ','), director.end());
                        director = trim(director);
                        
                        std::string title;
                        i++;
                        int x = i;
                        for (int i = x; i < v.size(); i++) {
                            if (i < v.size() - 1) {
                                title.append(v[i] + " ");
                            } else {
                                std::string lastVal = v[i];
                                lastVal.erase(remove(lastVal.begin(), lastVal.end(), ','), lastVal.end());
                                title.append(lastVal);
                            }
                        }
                        std::string key = "D" + trim(director) + trim(title);
                        Customer* cust = Store::StoreCustomerDatabase.search(stoi(customerID));
                        Movie* movie = Store::StoreInventory.search(cstoi(key));
                        cust -> returnMovie(*movie);
                    } else if (movieType == "C") { //Classic
                        std::string month;
                        std::string year;
                        std::string firstName;
                        std::string lastName;

                        month = v[4];
                        year = v[5];
                        firstName = v[6];
                        lastName = v[7];
                        std::string key = "C" + month + " " + year + firstName + " "+ lastName;
                        Customer* cust = Store::StoreCustomerDatabase.search(stoi(customerID));
                        Classic* movie = Store::StoreInventory.classicSearch(cstoi(key));
                        cust -> returnMovie(*movie);
                    } else {
                        cerr << "Error: invalid movie type '" << movieType << "'" << endl;
                    }
                }
            }
                break;
            default: {
                cerr << "Error: invalid command type '" << currentCommand[0] << "'" << endl;
            }
        }
    }
}

void Store::readCustomers(std::string &fileName) {
    int customerID;
    std::string firstName;
    std::string LastName;
    ifstream data;
    cout << "Opening Customer file" << endl;
    data.open(fileName);
    if (!data) {
        cerr << "Error: file '" << fileName << "' could not be opened" << endl;
        exit(1);
    }
    cout << "Customer file opened" << endl;
    while ( !data.eof()) {
        data >> customerID >> LastName >> firstName;
        cout << customerID << " " << firstName << " " << LastName << endl;
        Customer *cust = new Customer(customerID, firstName, LastName);
        StoreCustomerDatabase.insert(customerID, cust);
        cout << "Customer created and added successfully" << endl << endl;
    }
}
 
std::string Store::ltrim(const std::string &s) {
    size_t start = s.find_first_not_of(WHITESPACE);
    return (start == std::string::npos) ? "" : s.substr(start);
}
 
std::string Store::rtrim(const std::string &s) {
    size_t end = s.find_last_not_of(WHITESPACE);
    return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}
 
std::string Store::trim(const std::string &s) {
    return rtrim(ltrim(s));
}
