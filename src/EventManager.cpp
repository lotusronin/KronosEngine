#include "EventManager.h"
#include <iostream>

EventManager::EventManager() {
}

EventManager::~EventManager() {
    for(auto e : events) {
        delete e;
    }
}

void EventManager::addEvent(GameEvent* event) {
    if (event != NULL) {
        events.push_back(event); 
    } else {
        std::cout << "Cannot add a null event\n";
    }
}

//Function to process in game events.
//Will be specialized for each game
//Via callbacks
void EventManager::processEvents() {
    for(auto event : events) {
        event->process();
        delete event;
    }
}
