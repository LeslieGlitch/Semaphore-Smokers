/*
 * main.cpp
 *
 * Start of program, creates all threads and joins afterwards
 */

#include <iostream>
#include <pthread.h>
#include <mutex>
#include <string>
#include <cstdlib>
#include <unistd.h>

// Function Declarations
void *AgentLogicTP(void*);
void *AgentLogicPM(void*);
void *AgentLogicMT(void*);
void *PusherLogicTobacco(void*);
void *PusherLogicPaper(void*);
void *PusherLogicMatch(void*);
void *SmokerLogicTobacco(void*);
void *SmokerLogicPaper(void*);
void *SmokerLogicMatch(void*);

// Global variables
bool isTobacco = false;
bool isPaper = false;
bool isMatch = false;
std::mutex tobaccoSem;
std::mutex paperSem;
std::mutex matchSem;
std::mutex agentSem;
std::mutex tobacco;
std::mutex paper;
std::mutex match;
std::mutex mutex;

int main() {
    std::cout << "\nCigarette Smokers' Problem\n";

    // Lock starting semaphores
    tobaccoSem.lock();
    paperSem.lock();
    matchSem.lock();
    tobacco.lock();
    paper.lock();
    match.lock();

    // Seed RNG
    std::srand(std::time({}));

    // Create threads
    pthread_t Agent[3], Pusher[3], Smoker[6];
    // Agent
    if (pthread_create(&Agent[0], NULL, AgentLogicTP, NULL)) { std::cout << "Error: Agent thread failed to create!"; }
    if (pthread_create(&Agent[1], NULL, AgentLogicPM, NULL)) { std::cout << "Error: Agent thread failed to create!"; }
    if (pthread_create(&Agent[2], NULL, AgentLogicMT, NULL)) { std::cout << "Error: Agent thread failed to create!"; }
    // Pusher
    if (pthread_create(&Pusher[0], NULL, PusherLogicTobacco, NULL)) { std::cout << "Error: Pusher thread failed to create!"; }
    if (pthread_create(&Pusher[1], NULL, PusherLogicPaper, NULL)) { std::cout << "Error: Pusher thread failed to create!"; }
    if (pthread_create(&Pusher[2], NULL, PusherLogicMatch, NULL)) { std::cout << "Error: Pusher thread failed to create!"; }
    // Smoker
    if (pthread_create(&Smoker[0], NULL, SmokerLogicTobacco, NULL)) { std::cout << "Error: Smoker thread failed to create!"; }
    if (pthread_create(&Smoker[1], NULL, SmokerLogicTobacco, NULL)) { std::cout << "Error: Smoker thread failed to create!"; }
    if (pthread_create(&Smoker[2], NULL, SmokerLogicPaper, NULL)) { std::cout << "Error: Smoker thread failed to create!"; }
    if (pthread_create(&Smoker[3], NULL, SmokerLogicPaper, NULL)) { std::cout << "Error: Smoker thread failed to create!"; }
    if (pthread_create(&Smoker[4], NULL, SmokerLogicMatch, NULL)) { std::cout << "Error: Smoker thread failed to create!"; }
    if (pthread_create(&Smoker[5], NULL, SmokerLogicMatch, NULL)) { std::cout << "Error: Smoker thread failed to create!"; }

    // Join threads
    for (int i = 0; i < 3; ++i) {
        // Agent
        pthread_join(Agent[i], NULL);
    }
    for (int i = 0; i < 3; ++i) {
        // Pusher
        pthread_join(Pusher[i], NULL);
    }
    for (int i = 0; i < 6; ++i) {
        // Smoker
        pthread_join(Smoker[i], NULL);
    }

    return 0;
}

void *AgentLogicTP(void*) {
    for (int i = 0; i < 6; ++i) {
        agentSem.lock();
        // Set out Tobacco and Paper
        std::cout << "Agent set out Tobacco and Paper\n";
        tobacco.unlock();
        paper.unlock();
    }

    return (void*) NULL;
}

void *AgentLogicPM(void*) {
    for (int i = 0; i < 6; ++i) {
        agentSem.lock();
        // Set out Paper and Match
        std::cout << "Agent set out Paper and Match\n";
        paper.unlock();
        match.unlock();
    }

    return (void*) NULL;
}

void *AgentLogicMT(void*) {
    for (int i = 0; i < 6; ++i) {
        agentSem.lock();
        // Set out Match and Tobacco
        std::cout << "Agent set out Match and Tobacco\n";
        match.unlock();
        tobacco.unlock();
    }

    return (void*) NULL;
}

void *PusherLogicTobacco(void*) {
    for (int i = 0; i < 12; ++i) {
        tobacco.lock();
        mutex.lock();
        std::cout << "Tobacco Pusher locked mutex\n";
        if (isPaper) {
            isPaper = false;
            isTobacco = false;
            matchSem.unlock();
            std::cout << "Found Paper\n";
        }
        else if (isMatch) {
            isMatch = false;
            isTobacco = false;
            paperSem.unlock();
            std::cout << "Found Match\n";
        }
        else {
            isTobacco = true;
            std::cout << "Found no ingredients\n";
        }
        std::cout << "Tobacco Pusher unlocked mutex\n";
        mutex.unlock();
    }

    return (void*) NULL;
}

void *PusherLogicPaper(void*) {
    for (int i = 0; i < 12; ++i) {
        paper.lock();
        mutex.lock();
        std::cout << "Paper Pusher locked mutex\n";
        if (isMatch) {
            isMatch = false;
            isPaper = false;
            tobaccoSem.unlock();
            std::cout << "Found Match\n";
        }
        else if (isTobacco) {
            isTobacco = false;
            isPaper = false;
            matchSem.unlock();
            std::cout << "Found Tobacco\n";
        }
        else {
            isPaper = true;
            std::cout << "Found no ingredients\n";
        }
        std::cout << "Paper Pusher unlocked mutex\n";
        mutex.unlock();
    }

    return (void*) NULL;
}

void *PusherLogicMatch(void*) {
    for (int i = 0; i < 12; ++i) {
        match.lock();
        mutex.lock();
        std::cout << "Match Pusher locked mutex\n";
        if (isTobacco) {
            isTobacco = false;
            isMatch = false;
            paperSem.unlock();
            std::cout << "Found Tobacco\n";
        }
        else if (isPaper) {
            isPaper = false;
            isMatch = false;
            tobaccoSem.unlock();
            std::cout << "Found Paper\n";
        }
        else {
            isMatch = true;
            std::cout << "Found no ingredients\n";
        }
        std::cout << "Match Pusher unlocked mutex\n";
        mutex.unlock();
    }

    return (void*) NULL;
}

void *SmokerLogicTobacco(void*) {
    for (int i = 0; i < 3; ++i) {
        tobaccoSem.lock();
        std::cout << "Tobacco Smoker smoked a cigarrette\n";
        agentSem.unlock();
        usleep(5000);
    }

    std::cout << "Tobacco Smoker complete\n";
    return (void*) NULL;
}

void *SmokerLogicPaper(void*) {
    for (int i = 0; i < 3; ++i) {
        paperSem.lock();
        std::cout << "Paper Smoker smoked a cigarrette\n";
        agentSem.unlock();
        usleep(5000);
    }

    std::cout << "Paper Smoker complete\n";
    return (void*) NULL;
}

void *SmokerLogicMatch(void*) {
    for (int i = 0; i < 3; ++i) {
        matchSem.lock();
        std::cout << "Match Smoker smoked a cigarrette\n";
        agentSem.unlock();
        usleep(5000);
    }

    std::cout << "Match Smoker complete\n";
    return (void*) NULL;
}

