#include "JobTable.hpp"

// Default constructor for JobTable class. Initializes table of jobs 
// Precondition: None
// Postcondition: JobTable class is created
JobTable::
JobTable(){
    for (int i = 0; i < 10; i++){
        table[i] = new Job();
    }
}