/*
 * Pusher.cpp
 *
 * Pusher thread logic
 * Recieves notification from Agent, wakes up one of the Smokers
 */

 #include <iostream>
 #include "Pusher.h"

 void *PusherLogic(void*) {
    std::cout << "Pusher test!\n";
    return (void*) NULL;
}
