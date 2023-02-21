# Self-Evaluation

## Name(s): Andrzej Dawiec and Bastien Orbigo

Out of 25 points. Use output.txt created using 
`./create-output.sh > output.txt 2>&1` for guidance.

Complete all questions with "Q:"

Q: Does the program compile and run to completion: YES


- If the program does not compile or gives a segmentation error when run, 
the maximum possible grade is 50%. No need to continue with the rest of self-evaluation

Q: All public functions have been implemented: YES

- -2 for each functionality not implemented

For each command, state Full, Partial or None to indicate 
if it has been fully, partially or not implemented at all.
Explain any partial implementations.

Inventory: Full
History: Full
Borrow: Full
Return: Full


Q: -1 for each compilation warning, min -3: 0

- Check under *1. Compiles without warnings*
- If the warning message is addressed in README.md, including how the programmer tried to address it, no deductions

Q: -1 for each clang-tidy warning, min -3: ENTER_NUMBER TO DO 

- Check under *3. clang-tidy warnings*
- If the warning message is addressed in README.md, including how the programmer tried to address it, no deductions

Q: -1 for each clang-format warning, min -3: ENTER_NUMBER TO DO

- Check under *4. clang-format does not find any formatting issues*

Q: -2 for any detected memory leak: 0

- Check under *5. No memory leaks using g++*
- Check under *6. No memory leaks using valgrind*

Q: Do the tests sufficiently test the code: YES

- -1 for each large block of code not executed
- -2 for each function that is never called when testing
- Check under *7. Tests have full code coverage* paying attention to *The lines below were never executed*

Q: Are all functions in .h and .cpp file documents (min -3): YES

- -1 for each function not documented

## Location of error message or functionality

State the file and function where the information can be found

invalid command code: storeManager.cpp - getCommands()

invalid movie type: storeManager.cpp - getMovie()

invalid customer ID: storeManager.cpp - getCustomer()
 
invalid movie: storeManager.cpp - getMovie()

factory classes: StoreBuilder.cpp -> addStore()

hashtable: used in two spots, has one class MovieHash and one class CustomerHash. MovieHash hashes an ID for the movie assigned to the Movie object. For the CustomerHash, hashes the Customer ID assigned to the Customer data, all of which are tracked in the CustomerDatabase and MovieInventory classes.

container used for comedy movies: static MovieInventory StoreInventory

function for sorting comedy movies: TODO(student)

function where comedy movies are sorted: TODO(student)

functions called when retrieving a comedy movie based on title and year: TODO(student)

functions called for retrieving and printing customer history: TODO(student)

container used for customer history: A vector is implemented into the customer.h and customer.cpp files, called transactionHistory, in which a string of the entire Movie details and the borrow/return are tracked.

functions called when borrowing a movie: When borrowing, the getGenre() is used first to find the genre of the movie. From there, the search function is used by key to locate the key and value location in the database. getStock() is used to validate that there is still a movie to check out, then a getReleaseYear() is used with getTitle() to get the Movie information. addMovie() is used to add it to checked out movies, then getStock() is used to modify the stock and getReleaseYear() and getTitle() are used once more to get a message for the transaction history. 

explain borrowing a movie that does not exist: Each Movie is hashed with a key, and so when the borrowMovie() method is invoked, it gets the key from the Movie passed in. From there, the first check is if the search method based on the key returns a nullptr, which if it does, it creates a string error message that is pushed onto the transactionHistory vector. 

explain borrowing a movie that has 0 stock: Once the key is created, the Movie is searched for by key, checking if the key position is either nullptr or if the stock at that key is 0, creating an error message that is pushed onto the transactionHistory vector.

explain returning a movie that customer has not checked out: returnMovie() loops through the currentMovies (which tracks the current movies check out), setting movieBorrowed to true if it's present in the list, otherwise, movieBorrowed remains false and the first statement executes, building a string message that is pushed onto the transactionHistory vector.

any static_cast or dynamic_cast used: none


Q: Total points: ADD_ALL_POINTS (max 25)
