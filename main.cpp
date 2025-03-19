/*
 * main.cpp
 *
 * Start of program, creates all threads and joins afterwards
 */

#include <iostream>
#include <pthread.h>
#include <mutex>

// Settings
const int numAgents = 3;
const int numPushers = 3;
const int numSmokers = 6;

// Function Declarations
void *AgentLogic(void*);
void *PusherLogic(void*);
void *SmokerLogic(void*);

int main() {
    std::cout << "\nCigarette Smokers' Problem\n";

    // Create threads
    pthread_t Agent[numAgents], Pusher[numPushers], Smoker[numSmokers];
    for (int i = 0; i < numAgents; ++i) {
        // Agent
        if (pthread_create(&Agent[i], NULL, AgentLogic, NULL)) { std::cout << "Error: Agent thread failed to create!"; }
    }
    for (int i = 0; i < numPushers; ++i) {
        // Pusher
        if (pthread_create(&Pusher[i], NULL, PusherLogic, NULL)) { std::cout << "Error: Pusher thread failed to create!"; }
    }
    for (int i = 0; i < numSmokers; ++i) {
        // Smoker
        if (pthread_create(&Smoker[i], NULL, SmokerLogic, NULL)) { std::cout << "Error: Smoker thread failed to create!"; }
    }

    // Join threads
    for (int i = 0; i < numAgents; ++i) {
        // Agent
        pthread_join(Agent[i], NULL);
    }
    for (int i = 0; i < numPushers; ++i) {
        // Pusher
        pthread_join(Pusher[i], NULL);
    }
    for (int i = 0; i < numSmokers; ++i) {
        // Smoker
        pthread_join(Smoker[i], NULL);
    }

    return 0;
}

void *AgentLogic(void*) {
    std::cout << "Agent test!\n";
    return (void*) NULL;
}

void *PusherLogic(void*) {
    std::cout << "Pusher test!\n";
    return (void*) NULL;
}

void *SmokerLogic(void*) {
    std::cout << "Smoker test!\n";
    return (void*) NULL;
}

