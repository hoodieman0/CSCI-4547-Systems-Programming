#include "JobTable.hpp"

// Default constructor for JobTable class. Initializes table of jobs 
// Precondition: None
// Postcondition: JobTable class is created
JobTable::
JobTable(){
    for (int i = 0; i < 10; i++){
        // TODO check this assignment is not only the address
        table[i] = new Job();
    }
}

// Destructor for JobTable. Since "table" is dynamically allocated, call delete on it 
// Precondition: JobTable class exists
// Postcondition: JobTable class is deleted
JobTable::
~JobTable(){
    for (int i = 0; i < 10; i++){
        delete table[i];
    }
}