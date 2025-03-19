/*
 * Agent.cpp
 *
 * Agent thread logic
 * Randomly generates two ingredients and notifies Pushers
 */

 #include <iostream>
 #include "Agent.h"

void *AgentLogic(void*) {
    std::cout << "Agent test!\n";
    return (void*) NULL;
}
