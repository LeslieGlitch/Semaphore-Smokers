/*
 * Smoker.cpp
 *
 * Smoker thread logic
 * When woken, will smoke a cigarrette for a bit before waiting for more ingredients
 */

 #include <iostream>
 #include "Smoker.h"

 void *SmokerLogic(void*) {
    std::cout << "Smoker test!\n";
    return (void*) NULL;
}
